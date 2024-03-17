#!/bin/bash

rcfile="$HOME/.$(basename "$SHELL")rc"

crdir() {
  if [ ! -d "$1" ]; then
    mkdir -p "$1"
  fi
}

crdir "$HOME/ultra"
gcc -o "$HOME/ultra/ultra" "src/basic/basic.c" "src/download/download.c" "src/package/package.c" "src/packagelist/packagelist.c" "src/ultra/ultra.c" "src/ultrahttp/ultrahttp.c" "src/ultrazip/ultrazip.c" -std=c99 
