#include "Global.hpp"
#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
#include <iostream>

Global::Global() {}

SDL_Renderer* Global::init(const std::string& title, Uint32 flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "FAILED: SDL Init Everything" << std::endl;
        return nullptr;
    }

    // int imgFlags = IMG_INIT_PNG;
    // if (!(IMG_Init(imgFlags) & imgFlags))
    // {
    //     std::cerr << "SDL_image could not initialize! Error:" << IMG_GetError() << std::endl;
    //     return nullptr;
    // }

    // // Initialize SDL_ttf
    // if (TTF_Init() < 0)
    // {
    //     std::cerr << "SDL_ttf could not initialize! Error:" << TTF_GetError() << std::endl;
    //     return nullptr;
    // }

    // Create window
    pWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, flags);
    if (!pWindow)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Get window surface
    pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
    if (!pRenderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
        return nullptr;
    }

    return pRenderer;
}

Global::~Global()
{
    if (pRenderer)
        SDL_DestroyRenderer(pRenderer);
    pRenderer = nullptr;

    // Destroy window
    if (pWindow)
        SDL_DestroyWindow(pWindow);
    pWindow = nullptr;

    // Quit SDL subsystems
    // TTF_Quit();
    // IMG_Quit();

    // Quit SDL system
    SDL_Quit();
}
