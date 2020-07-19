#include "CApp.hpp"
#include <string>
#include <iostream>
#include <cmath>
#include <chrono>
#include "fractal.hpp"

CApp::CApp() {}

bool CApp::init()
{
    pRenderer = mGlobal.init("Pad Type", SDL_WINDOW_SHOWN);
    if (!pRenderer)
        return false;

    SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    for (int i = 0; i < PALLET_SIZE; ++i)
    {
        mRgbPalette[i][0] = ((i * 7) % 0xD0) + 0x2F;
        mRgbPalette[i][1] = ((i * 11) % 0xD0) + 0x2F;
        mRgbPalette[i][2] = ((i * 13) % 0xD0) + 0x2F;
    }
    mRgbPalette[PALLET_SIZE][0] = mRgbPalette[PALLET_SIZE][1] = mRgbPalette[PALLET_SIZE][2] = 0;

    mView = { Global::SCREEN_WIDTH, Global::SCREEN_HEIGHT, PALLET_SIZE/4 };
    mBuildView = { Global::SCREEN_WIDTH, Global::SCREEN_HEIGHT, PALLET_SIZE, {0,0} };

    mRunning = true;
    return true;
}

void CApp::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            mRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (SDL_BUTTON_LEFT == e.button.button)
            {
                std::cout << "Button: X=" << e.button.x << ", Y=" << e.button.y << "\n";
                mView.center = { mView.center.real()
                        + (e.button.x - Global::SCREEN_WIDTH / 2) * mView.scale * mView.aspect,
                    mView.center.imag() - (e.button.y - Global::SCREEN_HEIGHT / 2) * mView.scale };
            }
            else if (SDL_BUTTON_RIGHT == e.button.button)
            {
                std::cout << "Reset on Right Click\n";
                mView = {Global::SCREEN_WIDTH,  Global::SCREEN_HEIGHT, PALLET_SIZE};
            }
            else if (SDL_BUTTON_MIDDLE == e.button.button)
            {
                std::cout << "Toggle resolution\n";
                mView.depth = (mView.depth == PALLET_SIZE ? PALLET_SIZE/4 : PALLET_SIZE);
            }
            break;
        case SDL_MOUSEWHEEL:
            if(e.wheel.y > 0)
                mView.scale *= 0.8;
            else if( e.wheel.y < 0)
                mView.scale *= 1.25;

            std::cout << "Scale:" << mView.scale << "\n";

            break;
        default:
            break;
        }
    }
}

int CApp::execute()
{
    if (!init())
        return -1;

    while (mRunning)
    {
        handleEvents();
        update();
        render();
    }

    return 0;
}

void CApp::update()
{
    SDL_Color text_color { 0, 0, 0 };

    auto status = std::future_status::ready;
    if (mAsyncWork.valid())
    {
        status = mAsyncWork.wait_for(std::chrono::milliseconds(1));
    }
    if ((status == std::future_status::ready) && !(mBuildView == mView))
    {
        std::complex<double> bottom_left
            = { mView.center.real() - Global::SCREEN_WIDTH / 2 * mView.scale * mView.aspect,
                  mView.center.imag() - Global::SCREEN_HEIGHT / 2 * mView.scale };

        std::complex<double> top_right
            = { mView.center.real() + Global::SCREEN_WIDTH / 2 * mView.scale * mView.aspect,
                  mView.center.imag() + Global::SCREEN_HEIGHT / 2 * mView.scale };
        std::cout << "Contructing Mandlebrot: " << bottom_left << " : " << top_right << "\n";

        mBuildView = mView;
        mAsyncWork = std::async(std::launch::async, [this]() -> bool {
            Fractal::mandlebrot(mBuildView, [this](int x, int y, int c) { mPlot[y][x] = c; });
            return true;
        });

        SDL_Delay(1000 / 80);
    }
}

void CApp::render()
{
    SDL_RenderClear(pRenderer);

    // @TODO: Add stuff to render
    SDL_Rect outlineRect = { Global::SCREEN_WIDTH / 6, Global::SCREEN_HEIGHT / 6,
        Global::SCREEN_WIDTH * 2 / 3, Global::SCREEN_HEIGHT * 2 / 3 };

    SDL_SetRenderDrawColor(pRenderer, 0x00, 0x00, 0x00, 0xFF);

    for (int y = 0; y < Global::SCREEN_HEIGHT; ++y)
    {
        for (int x = 0; x < Global::SCREEN_WIDTH; ++x)
        {
            int c = mPlot[y][x];
            SDL_SetRenderDrawColor(
                pRenderer, mRgbPalette[c][0], mRgbPalette[c][1], mRgbPalette[c][2], 0xFF);
            SDL_RenderDrawPoint(pRenderer, x, y);
        }
    }

    SDL_SetRenderDrawColor(pRenderer, 0x00, 0x00, 0x00, 0xFF);

    // Update the surface
    SDL_RenderPresent(pRenderer);
}

CApp::~CApp() {}