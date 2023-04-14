#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Application.hpp"

int main(int argc, char** argv)
{
    SDL_SetMainReady();

    Application application;
    if (!application.is_initialized())
    {
        return -1;
    }
    application.run();
    return 0;
}
