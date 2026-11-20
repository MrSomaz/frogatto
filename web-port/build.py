#!/usr/bin/env python3
"""Build Anura (Frogatto engine) for WebAssembly with Emscripten."""
import os, sys, subprocess, glob, concurrent.futures as cf

ROOT = r"D:/frogatto-web"
EM = ROOT + "/emsdk/upstream/emscripten"
SRC = ROOT + "/anura/src"
OBJ = ROOT + "/obj"
OUT = ROOT + "/out"
os.environ["EM_CONFIG"] = ROOT + "/emsdk/.emscripten"
os.environ["EMSDK_PYTHON"] = ROOT + "/emsdk/python/3.13.3_64bit/python.exe"
os.environ["EMSDK_NODE"] = ROOT + "/emsdk/node/24.19.0_64bit/node.exe"

PORTS = [
    "-sUSE_SDL=2", "-sUSE_SDL_IMAGE=2", '-sSDL2_IMAGE_FORMATS=["png","jpg"]',
    "-sUSE_SDL_MIXER=2", '-sSDL2_MIXER_FORMATS=["ogg"]', "-sUSE_SDL_TTF=2",
    "-sUSE_FREETYPE=1", "-sUSE_ZLIB=1", "-sUSE_LIBPNG=1", "-sUSE_OGG=1",
    "-sUSE_VORBIS=1", "-sUSE_BOOST_HEADERS=1",
]
OPT = os.environ.get("OPT", "-O2")
CXXFLAGS = [
    "-std=c++17", "-pthread", "-fwasm-exceptions", "-sSUPPORT_LONGJMP=wasm", OPT, "-w", "-Wno-c++11-narrowing", "-include", "cfloat",
    "-I" + ROOT + "/shim", "-I" + ROOT + "/deps/prefix/include",
    "-I" + ROOT + "/glm", "-I" + ROOT + "/imgui",
    "-I" + SRC, "-I" + SRC + "/hex", "-I" + SRC + "/imgui_additions",
    "-I" + SRC + "/kre", "-I" + SRC + "/svg", "-I" + SRC + "/tiled",
    "-I" + SRC + "/treetree", "-I" + SRC + "/xhtml",
    '-DIMGUI_USER_CONFIG="' + SRC + '/imgui_additions/imconfig_anura.h"',
    "-DIMGUI_DEFINE_MATH_OPERATORS", "-DGLM_ENABLE_EXPERIMENTAL",
    "-DNO_EDITOR_OVERRIDE_DISABLED",
    "-DBOOST_FILESYSTEM_NO_CXX20_ATOMIC_REF",
] + PORTS

EXCLUDE = {
    "StackWalker.cpp", "filesystem-android.cpp", "stats_server_main.cpp",
}

def sources():
    files = [ROOT + "/shim/web_stubs.cpp"] + [ROOT + "/imgui/" + f for f in ("imgui.cpp", "imgui_draw.cpp", "imgui_tables.cpp", "imgui_widgets.cpp")]
    for d in ("", "hex/", "imgui_additions/", "kre/", "svg/", "tiled/", "treetree/", "xhtml/"):
        for f in sorted(glob.glob(SRC + "/" + d + "*.cpp")):
            if os.path.basename(f) in EXCLUDE:
                continue
            files.append(f.replace("\\", "/"))
    return files

def objname(src):
    rel = os.path.relpath(src, ROOT).replace("\\", "/").replace("/", "__")
    return OBJ + "/" + rel[:-4] + ".o"

def compile_one(src):
    obj = objname(src)
    if os.path.exists(obj) and os.path.getmtime(obj) > os.path.getmtime(src) and not os.environ.get("FORCE"):
        return src, 0, ""
    cmd = [EM + "/em++.exe"] + CXXFLAGS + ["-c", src, "-o", obj]
    p = subprocess.run(cmd, capture_output=True, text=True, errors="replace")
    return src, p.returncode, p.stderr

def main():
    os.makedirs(OBJ, exist_ok=True)
    os.makedirs(OUT, exist_ok=True)
    only = sys.argv[1:] if len(sys.argv) > 1 and sys.argv[1] != "link" else None
    srcs = sources()
    if only:
        srcs = [s for s in srcs if any(o in s for o in only)]
    failed = []
    if sys.argv[1:2] != ["link"]:
        with cf.ThreadPoolExecutor(max_workers=int(os.environ.get("JOBS", "14"))) as ex:
            for src, rc, err in ex.map(compile_one, srcs):
                if rc != 0:
                    failed.append(src)
                    print("FAIL", src)
                    print("\n".join([l for l in err.splitlines() if "error" in l][:6]))
        print("compiled; failed:", len(failed))
        if failed or only:
            return 1 if failed else 0
    objs = [objname(s) for s in sources()]
    link = [EM + "/em++.exe", "-pthread", "-fwasm-exceptions", "-sSUPPORT_LONGJMP=wasm", OPT] + PORTS + objs + [
        ROOT + "/deps/prefix/lib/libcairo.a", ROOT + "/deps/prefix/lib/libpixman-1.a",
        ROOT + "/deps/prefix/lib/libboost_filesystem.a",
        "-sMIN_WEBGL_VERSION=2", "-sMAX_WEBGL_VERSION=2", "-sFULL_ES3=1",
        "-sALLOW_MEMORY_GROWTH=1", "-sINITIAL_MEMORY=512MB", "-sMAXIMUM_MEMORY=4GB",
        "-sSTACK_SIZE=8MB", "-sDEFAULT_PTHREAD_STACK_SIZE=4MB",
        "-sPTHREAD_POOL_SIZE=12", "-sPTHREAD_POOL_SIZE_STRICT=0",
        "-sJSPI=1", "-sEXIT_RUNTIME=0", "-sFORCE_FILESYSTEM=1",
        "-sEXPORTED_RUNTIME_METHODS=['FS','callMain','IDBFS']", "-sINVOKE_RUN=0",
        "-lidbfs.js", "-sOFFSCREEN_FRAMEBUFFER=0",
        "-o", OUT + "/anura.js",
    ] + os.environ.get("LINKFLAGS", "").split()
    print("linking", len(objs), "objects")
    p = subprocess.run(link, capture_output=True, text=True, errors="replace")
    print(p.stdout[-4000:], p.stderr[-12000:])
    return p.returncode

if __name__ == "__main__":
    sys.exit(main())
