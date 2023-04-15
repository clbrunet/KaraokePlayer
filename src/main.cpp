#include <cassert>
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "glad/gl.h"

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
	assert(glGetError() == GL_NO_ERROR);
    return 0;
}
