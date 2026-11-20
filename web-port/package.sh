#!/bin/sh
# Re-package game data (excluding sounds, which have their own package)
. /d/frogatto-web/env.sh
cd /d/frogatto-web && python emsdk/upstream/emscripten/tools/file_packager.py web/game.data --preload "D:/frogatto-web/game@/game" --exclude "D:/frogatto-web/game/modules/frogatto4/sounds/*" --js-output=web/game.data.js --use-preload-cache --no-node 2>&1 | grep -v "warning: Remember"
ls -la web/game.data | awk '{print $5}'
