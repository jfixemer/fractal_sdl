#pragma once
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>
#include "Global.hpp"
#include "fractal.hpp"
#include <future>
#include <array>

class CApp
{
public:
    CApp();
    ~CApp();

    int execute();

private:
    bool init();
    void handleEvents();
    void update();
    void render();

    static const int PALLET_SIZE = 255;

    Global  mGlobal;
    // SDL_Renderer lifetime is owned by mGlobal.
    // This is a cache value for easy access.
    SDL_Renderer* pRenderer = nullptr;
    bool mRunning = false;

    Fractal::view mView;
    Fractal::view mBuildView;
    std::future<bool> mAsyncWork;
    std::array<std::array<uint8_t, 3>, PALLET_SIZE+1> mRgbPalette;
    std::array<std::array<uint8_t, Global::SCREEN_WIDTH>, Global::SCREEN_HEIGHT> mPlot;
};

#endif