# Frogatto & Friends — web port

Unofficial, non-commercial port of Frogatto & Friends to the browser (WebAssembly + WebGL 2).
Live build: https://frogatto-nu.vercel.app

Needs a recent Chrome or Edge (WebAssembly JSPI + SharedArrayBuffer).

## How it works

- The [Anura engine](https://github.com/anura-engine/anura) is compiled with Emscripten
  (`-pthread -fwasm-exceptions -sJSPI -sFULL_ES3`). `anura-web.patch` holds the engine changes:
  - yield to the browser after every buffer swap (JSPI `emscripten_sleep(0)`),
  - request a WebGL 2 context and translate desktop GLSL to GLSL ES,
  - load `.ogg` sound effects instead of `.wav`,
  - download music tracks on first use instead of preloading them,
  - small fixes for missing GL functions, `boost::locale` and `glMapBuffer`.
- `shim/GL/glew.h` replaces GLEW with GLES 3 headers plus desktop-only enums/stubs.
- `web/glsl-patch.js` rewrites shaders to GLSL ES 3.00 and converts BGRA texture uploads to RGBA at runtime.
- Cairo 1.18.2, pixman 0.43.4 and Boost.Filesystem 1.83 are built from source with `emcc`
  (same flags); SDL2, SDL2_image/mixer/ttf, freetype, libpng, ogg/vorbis come from Emscripten ports.

## Build

1. Install emsdk, clone `anura-engine/anura`, apply `anura-web.patch`, clone imgui v1.89.7 and glm 1.0.0.
2. Build cairo/pixman/boost-filesystem into `deps/prefix` (see `build.py` for paths).
3. `python build.py && python build.py link` → `out/anura.{js,wasm}`.
4. Stage the game in `game/` (`data`, `images`, `modules/{gui,icons,lib_2d,tbs}` from Anura and this repo as
   `modules/frogatto4`), convert `sounds/*.wav` to `.ogg`, replace music with zero-byte placeholders and put the
   re-encoded tracks in `web/music/`.
5. `./package.sh` (plus a separate `sounds.data` package) and deploy `web/` with the COOP/COEP headers in `vercel.json`.

## License

Game content: CC-BY 3.0, with levels, characters, tiles, sounds and music under CC-BY-NC-SA 4.0 (see `../LICENSE`).
Engine: zlib. This port is non-commercial.
