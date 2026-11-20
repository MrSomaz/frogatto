#!/bin/sh
# Incremental compile + link + copy to web/
cd /d/frogatto-web && python build.py "$@" | grep -v "^compiled; failed: 0" ; LINKFLAGS="$LINKFLAGS" python build.py link > link.log 2>&1; grep -i "error" link.log | head; cp out/anura.* web/ && ls -la web/anura.wasm | awk '{print $5, $6, $7, $8}'
