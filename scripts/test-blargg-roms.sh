#!/bin/bash

cd "$(dirname "$0")"

emulator="../build/test/test-emulator"
romdir=

for filename in ../test/gb-test-roms/cpu_instrs/individual/*.gb; do
  $emulator "$filename"
done
