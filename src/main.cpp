#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Program.hpp"

int main(int argc, char** argv)
{
    SDL_SetMainReady();

    Program program;
    if (!program.is_initialized())
    {
        return -1;
    }
    program.run();

    return 0;
}
