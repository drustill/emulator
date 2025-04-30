#!/bin/bash

cd "$(dirname "$0")"

GREEN='\033[1;32m'
RED='\033[1;31m'
CLEAR='\033[0m'

emulator="../build/test/test-emulator"

echo ""

for filename in ../test/gb-test-roms/cpu_instrs/individual/*.gb; do

  testname=$(basename "$filename")
  printf "%--40s" "$testname"

  $emulator "$filename" | grep "Passed" > /dev/null 2>&1

  if [ $? -eq 0 ]; then
    printf "${GREEN} Passed ${CLEAR}\n"
  else
    printf "${RED} Failed ${CLEAR}\n"
  fi

done
