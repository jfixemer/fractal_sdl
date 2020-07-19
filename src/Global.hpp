#pragma once
#ifndef SDL_GLOBAL_HPP
#define SDL_GLOBAL_HPP
#include <string>
#include <stdint.h>

struct SDL_Window;
struct SDL_Renderer;
using Uint32 = uint32_t;

class Global
{
public:
    Global();
    ~Global();
    SDL_Renderer* init(const std::string& title, Uint32 flags);
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;

private:
    SDL_Window* pWindow = nullptr;
    SDL_Renderer* pRenderer = nullptr;
};

#endif