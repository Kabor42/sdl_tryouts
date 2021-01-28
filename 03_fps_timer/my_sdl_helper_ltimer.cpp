#include "my_sdl_helper_ltimer.h"

#include <SDL2/SDL.h>

LTimer::LTimer() {
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start() {
    mStarted = true;
    mPaused = false;
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop() {
    mStarted = false;
    mPaused = true;
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause() {
    if(mStarted && !mPaused) {
        mPaused = true;
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

uint32_t LTimer::getTicks() {
    uint32_t time = 0;
    if (mStarted) {
        time = (mPaused) ? mPausedTicks : SDL_GetTicks() - mStartTicks;
    }
    return time;
}

bool LTimer::isStarted() { return mStarted; }
bool LTimer::isPaused() { return mPaused; }