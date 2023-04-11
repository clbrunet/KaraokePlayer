#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <cstdio>

int main(int argc, char** argv)
{
    SDL_SetMainReady();

    SDL_Window* window = SDL_CreateWindow("Karaoke Player"
        , SDL_WINDOWPOS_CENTERED
        , SDL_WINDOWPOS_CENTERED
        , 800, 600
        , SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fputs("Coundl't initialize video subsystem.\n", stderr);
        return -1;
    }

    if (!window)
    {
        fputs("Couldn't create SDL window.\n", stderr);
        return -1;
    }

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
            }
        }

        if (!running)
            break;

        // Rendering karaoke here
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
