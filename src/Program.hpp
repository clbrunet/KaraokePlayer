#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <SDL.h>

class Program
{
public:
    Program();
    Program(Program &&) = default;
    Program(const Program &) = default;
    Program &operator=(Program &&) = default;
    Program &operator=(const Program &) = default;
    ~Program();

    bool is_initialized();
    void run();

private:
    bool m_is_initialized;
    SDL_Window* m_window;
};

#endif
