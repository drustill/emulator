.PHONY: all build test clean

all: build

build:
	mkdir -p build
	cmake -S . -B build
	cmake --build build

test:
	./scripts/test-blargg-roms.sh

emu:
	./build/sdl/emulator

clean:
	rm -rf build
