#!/bin/sh
FILE="tetris.wasm"
emcc ./src/main.c -s STANDALONE_WASM -Oz -o $FILE --no-entry -s "EXPORTED_FUNCTIONS=_initGame,_getGame,_updateGame,_moveCurrentBlock"
mv $FILE ./wasm/$FILE
