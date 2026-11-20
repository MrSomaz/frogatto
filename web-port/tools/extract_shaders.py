"""Extract GLSL shader sources from the engine C++ and the game .cfg data for offline WebGL testing."""
import re, json, glob, os, sys

out = []

# 1. C++ string-literal shaders in the engine.
for path in glob.glob('D:/frogatto-web/anura/src/**/*.cpp', recursive=True):
    s = open(path, encoding='utf-8', errors='replace').read()
    for m in re.finditer(r'(?:"(?:[^"\\\n]|\\.)*"\s*)+', s):
        lits = re.findall(r'"((?:[^"\\\n]|\\.)*)"', m.group(0))
        txt = ''.join(lits)
        if 'void main' not in txt:
            continue
        txt = txt.replace('\\n', '\n').replace('\\t', '\t').replace('\\"', '"').replace('\\\\', '\\')
        kind = 'fs' if ('gl_FragColor' in txt or 'gl_FragData' in txt) else 'vs'
        out.append({'src': os.path.basename(path), 'kind': kind, 'code': txt})

# 2. Shaders embedded in FFL/cfg data: "vertex: \"...\"" / "fragment: \"...\"".
for path in glob.glob('D:/frogatto-web/game/**/*.cfg', recursive=True):
    s = open(path, encoding='utf-8', errors='replace').read()
    if 'void main' not in s:
        continue
    for m in re.finditer(r'\b(vertex|fragment)\s*:\s*"((?:[^"\\]|\\.)*?void\s+main(?:[^"\\]|\\.)*)"', s, re.S):
        kind = 'vs' if m.group(1) == 'vertex' else 'fs'
        code = m.group(2).replace('\\"', '"')
        out.append({'src': os.path.relpath(path, 'D:/frogatto-web/game'), 'kind': kind, 'code': code})

json.dump(out, open(sys.argv[1] if len(sys.argv) > 1 else 'D:/frogatto-web/web/_shaders.json', 'w'))
print(len(out), 'shaders;', sum(1 for o in out if o['src'].endswith('.cfg')), 'from cfg')
