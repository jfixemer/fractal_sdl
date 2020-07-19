# Mandlebrot rendered in SDL
A little program that uses SDL to create a Mandlebrot plot.

## How to build
1. `cd <build>; cmake -DCMAKE_GENERATOR_PLATFORM=[x64|x86] ..`
2. `cd build; cmake --build -j <N> . --target ext_sdl`
3. `cd build; rm CMakeCache.txt`
4. `cd build; cmake -DCMAKE_GENERATOR_PLATFORM=[x64|x86] ..`
5. `cmake --build -j <N> . [--config Release]`

## Features
- Left mouse click to select 'center'
- Right mouse click to 'reset'
- Mouse wheel to zoom in and out.
- Middle mouse click to toggle 'depth' for escape test.
  
## Build/Dev Features
- Windows CMake rules that build SDL from source.
  - A little clunky because I used external project and find package.  They don't play well together.
- A few modernish C++ items:
  - Wrap SDL_Init in a more RAII structure `Global` (but not 100% because I think folks avoid SDL_Init in constructor for reasons)
  - Fractal generation is a template.
  - Fractal plotting is provided via Lambda.
