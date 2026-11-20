// Desktop GLSL (1.10/1.20) is far more lenient than WebGL's GLSL ES.
// The engine hands us "#version 100" sources; we translate them to GLSL ES 3.00
// (WebGL 2) and fall back through progressively more aggressive fixes.
(function patchGLSL() {
  const P = WebGL2RenderingContext.prototype;
  const origSource = P.shaderSource, origCompile = P.compileShader;
  const pending = new WeakMap();

  const stripHeader = (s) => s
    .replace(/^#version.*$/m, '')
    .replace(/#ifdef GL_FRAGMENT_PRECISION_HIGH[\s\S]*?#endif\n?/, '')
    .split('\n').map((l) => /^\s*#\s*(version|extension)\b/.test(l) ? '' : l).join('\n')
    .replace(/^\s*precision\s+\w+\s+\w+\s*;/gm, '');

  const fixLiterals = (s) => s
    .replace(/(\d+\.\d*|\.\d+|\d+\.?\d*e[+-]?\d+)[fF]\b/g, '$1')
    .replace(/\b(\d+)[fF]\b/g, '$1.0');

  // Drop initializers on uniforms (not allowed in GLSL ES); keep the default by
  // turning "uniform T x = v;" into a #define-free global that the uniform overrides is not
  // possible, so we keep the declaration only.
  const fixUniformInit = (s) => s.replace(/\buniform\s+(\w+)\s+(\w+)\s*=\s*[^;]+;/g, 'uniform $1 $2;');

  const promoteInts = (s) => s.split('\n').map((line) => {
    const t = line.trim();
    if (/^#/.test(t) || /\b(int|ivec\d|bool|for|while|uint)\b/.test(t)) return line;
    return line.replace(/(\[[^\]]*\])|([\w.]?)\b(\d+)\b(?![.\w])/g, (m, br, pre, num) => {
      if (br) return br;
      if (pre && /[\w.]/.test(pre)) return m;
      return (pre || '') + num + '.0';
    });
  }).join('\n');

  // int loop counters used in float math: wrap "index" style ints used next to floats.
  const castIntVars = (s) => {
    const ints = new Set();
    s.replace(/\bint\s+(\w+)\s*[=;]/g, (m, n) => ints.add(n));
    s.replace(/for\s*\(\s*int\s+(\w+)/g, (m, n) => ints.add(n));
    if (!ints.size) return s;
    const re = new RegExp('([-+*/]\\s*)\\b(' + [...ints].join('|') + ')\\b(?!\\s*[\\[\\]])|\\b(' + [...ints].join('|') + ')\\b(\\s*[-+*/](?![-+=]))', 'g');
    return s.split('\n').map((line) => {
      if (/\bfor\s*\(|\[|\bint\b/.test(line)) return line;
      return line.replace(re, (m, op, n1, n2, op2) => n1 ? op + 'float(' + n1 + ')' : 'float(' + n2 + ')' + op2);
    }).join('\n');
  };

  const toES3 = (body, isFrag) => {
    let s = body;
    // "texture" becomes a builtin function in ES3; rename user identifiers called texture.
    s = s.replace(/\btexture\b(?!\s*\()/g, 'anura_texture');
    s = s.replace(/\b(in|out|sample|smooth|flat|centroid|layout|uint|patch|filter|packed)\b(?=\s*[;,)=\[.+\-*/])/g, 'anura_$1');
    s = s.replace(/\btexture2DLod\b/g, 'textureLod').replace(/\btexture2DProj\b/g, 'textureProj')
         .replace(/\btexture2D\b/g, 'texture').replace(/\btextureCube\b/g, 'texture').replace(/\btexture3D\b/g, 'texture');
    let head = '#version 300 es\nprecision highp float;\nprecision highp int;\nprecision highp sampler2D;\n';
    if (isFrag) {
      s = s.replace(/\bvarying\b/g, 'in');
      if (/\bgl_FragData\b/.test(s)) {
        head += 'out vec4 anura_FragData[4];\n';
        s = s.replace(/\bgl_FragData\b/g, 'anura_FragData');
      } else {
        head += 'out vec4 anura_FragColor;\n';
        s = s.replace(/\bgl_FragColor\b/g, 'anura_FragColor');
      }
    } else {
      s = s.replace(/\battribute\b/g, 'in').replace(/\bvarying\b/g, 'out');
    }
    return head + s;
  };

  const legacyES2 = (body) => '#version 100\nprecision highp float;\nprecision highp int;\n' + body;

  function candidates(src, isFrag) {
    const body = fixUniformInit(fixLiterals(stripHeader(src)));
    return [
      toES3(body, isFrag),
      toES3(castIntVars(body), isFrag),
      toES3(promoteInts(castIntVars(body)), isFrag),
      legacyES2(body),
      legacyES2(promoteInts(body)),
    ];
  }

  P.shaderSource = function (sh, src) {
    pending.set(sh, src);
    return origSource.call(this, sh, src);
  };
  P.compileShader = function (sh) {
    const src = pending.get(sh);
    if (src == null) return origCompile.call(this, sh);
    const isFrag = this.getShaderParameter(sh, this.SHADER_TYPE) === this.FRAGMENT_SHADER;
    const tries = candidates(src, isFrag);
    let firstLog = '';
    for (let i = 0; i < tries.length; i++) {
      origSource.call(this, sh, tries[i]);
      origCompile.call(this, sh);
      if (this.getShaderParameter(sh, this.COMPILE_STATUS)) return;
      if (i === 0) firstLog = this.getShaderInfoLog(sh);
    }
    (window.__glslFailures = window.__glslFailures || []).push({ src, log: firstLog });
    console.warn('GLSL translation failed:\n' + firstLog + '\n---\n' + tries[0]);
    origSource.call(this, sh, tries[0]);
    origCompile.call(this, sh);
  };
  window.__glslCandidates = candidates;
})();

// Desktop texture formats (BGRA, BGR, 8_8_8_8_REV, unsized internal formats with GL_RED…)
// are rejected by WebGL 2. Convert uploads to RGBA/UNSIGNED_BYTE on the fly.
(function patchTextures() {
  const P = WebGL2RenderingContext.prototype;
  const GL = {
    RED: 0x1903, RGB: 0x1907, RGBA: 0x1908, BGR: 0x80E0, BGRA: 0x80E1, LUMINANCE: 0x1909, ALPHA: 0x1906,
    UBYTE: 0x1401, U8888: 0x8035, U8888REV: 0x8367,
    R8: 0x8229, RGB8: 0x8051, RGBA8: 0x8058, RGBA4: 0x8056, RGB5_A1: 0x8057,
    UNPACK_ROW_LENGTH: 0x0CF2, UNPACK_SKIP_ROWS: 0x0CF3, UNPACK_SKIP_PIXELS: 0x0CF4, UNPACK_ALIGNMENT: 0x0CF5,
  };
  const origTexImage2D = P.texImage2D, origTexSubImage2D = P.texSubImage2D, origPixelStorei = P.pixelStorei;
  const unpack = new WeakMap();
  const st = (gl) => { let s = unpack.get(gl); if (!s) { s = { [GL.UNPACK_ROW_LENGTH]: 0, [GL.UNPACK_SKIP_ROWS]: 0, [GL.UNPACK_SKIP_PIXELS]: 0, [GL.UNPACK_ALIGNMENT]: 4 }; unpack.set(gl, s); } return s; };
  P.pixelStorei = function (p, v) { if (p in st(this)) st(this)[p] = v; return origPixelStorei.call(this, p, v); };

  // Re-pack a (possibly strided) source into tight RGBA bytes.
  function repack(gl, src, w, h, bpp, order) {
    const s = st(gl);
    const rowPixels = s[GL.UNPACK_ROW_LENGTH] || w;
    const align = s[GL.UNPACK_ALIGNMENT];
    const stride = Math.ceil((rowPixels * bpp) / align) * align;
    const base = src.byteOffset + s[GL.UNPACK_SKIP_ROWS] * stride + s[GL.UNPACK_SKIP_PIXELS] * bpp;
    const bytes = new Uint8Array(src.buffer);
    const out = new Uint8Array(w * h * 4);
    for (let y = 0; y < h; y++) {
      let i = base + y * stride, o = y * w * 4;
      for (let x = 0; x < w; x++, i += bpp, o += 4) {
        out[o] = bytes[i + order[0]]; out[o + 1] = bytes[i + order[1]]; out[o + 2] = bytes[i + order[2]];
        out[o + 3] = order[3] < 0 ? 255 : bytes[i + order[3]];
      }
    }
    return out;
  }
  function withTightUnpack(gl, fn) {
    const s = st(gl), saved = { ...s };
    origPixelStorei.call(gl, GL.UNPACK_ROW_LENGTH, 0); origPixelStorei.call(gl, GL.UNPACK_SKIP_ROWS, 0);
    origPixelStorei.call(gl, GL.UNPACK_SKIP_PIXELS, 0); origPixelStorei.call(gl, GL.UNPACK_ALIGNMENT, 1);
    try { return fn(); } finally { for (const k in saved) origPixelStorei.call(gl, +k, saved[k]); }
  }
  // Returns [byteOrder, bytesPerPixel] for formats needing conversion, else null.
  function conversion(format, type) {
    if (format === GL.BGRA && (type === GL.U8888REV || type === GL.UBYTE)) return [[2, 1, 0, 3], 4];
    if (format === GL.RGBA && type === GL.U8888REV) return [[0, 1, 2, 3], 4];
    if (format === GL.BGRA && type === GL.U8888) return [[1, 2, 3, 0], 4];
    if (format === GL.RGBA && type === GL.U8888) return [[3, 2, 1, 0], 4];
    if (format === GL.BGR && type === GL.UBYTE) return [[2, 1, 0, -1], 3];
    return null;
  }
  function fixInternal(internal, format, type) {
    if (format === GL.RED && type === GL.UBYTE) return GL.R8;
    if (format === GL.RGBA && type === GL.UBYTE) return GL.RGBA8;
    if (format === GL.RGB && type === GL.UBYTE) return GL.RGB8;
    if (format === GL.LUMINANCE || format === GL.ALPHA) return format;
    return internal;
  }

  P.texImage2D = function (target, level, internal, w, h, border, format, type, pixels, ...rest) {
    if (arguments.length >= 9 && typeof w === 'number') {
      const conv = conversion(format, type);
      if (conv) {
        const data = pixels && pixels.buffer ? repack(this, pixels, w, h, conv[1], conv[0]) : null;
        return withTightUnpack(this, () => origTexImage2D.call(this, target, level, GL.RGBA8, w, h, border, GL.RGBA, GL.UBYTE, data));
      }
      return origTexImage2D.call(this, target, level, fixInternal(internal, format, type), w, h, border, format, type, pixels, ...rest);
    }
    return origTexImage2D.apply(this, arguments);
  };
  P.texSubImage2D = function (target, level, x, y, w, h, format, type, pixels, ...rest) {
    if (arguments.length >= 9 && typeof w === 'number') {
      const conv = conversion(format, type);
      if (conv && pixels && pixels.buffer) {
        const data = repack(this, pixels, w, h, conv[1], conv[0]);
        return withTightUnpack(this, () => origTexSubImage2D.call(this, target, level, x, y, w, h, GL.RGBA, GL.UBYTE, data));
      }
    }
    return origTexSubImage2D.apply(this, arguments);
  };
})();
