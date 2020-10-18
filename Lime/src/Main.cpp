//
//  main.cpp
//  Lime
//
//  Created by Abhikalp Unakal on 11/10/2020
//  Copyright © 2020 Abhikalp Unakal. All rights reserved.
//

#include <iostream>
#include <SDL.h>
#ifdef _WIN64
    #include "Windows.h"
    FILE _iob[] = { 
        *stdin, 
        *stdout, 
        *stderr 
    };	
    extern "C" FILE * __cdecl __iob_func(void){
	    return _iob;
    }
    #pragma comment(lib, "legacy_stdio_definitions.lib")

     //allocating console
    void alloc_console() {
        if (AllocConsole())
        {
            FILE* file;

            freopen_s(&file, "CONOUT$", "wt", stdout);
            freopen_s(&file, "CONOUT$", "wt", stderr);
            freopen_s(&file, "CONOUT$", "wt", stdin);

            SetConsoleTitle(L"Lime");
        }
    }
#endif

int main(int argc, char** argv) {

    #ifdef _WIN64
    alloc_console();
    #endif // _WIN64

    int width = 512, height = 512;
    SDL_Window* window = SDL_CreateWindow("Lime", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);

    if (window == NULL)
        std::cout << "There was an error while initializing the window" << std::endl << SDL_GetError << std::endl;

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }
        SDL_GetWindowSize(window, &width, &height);

        SDL_Surface* surface = SDL_GetWindowSurface(window);
        Uint32 skyblue = SDL_MapRGB(surface->format, 65, 193, 193);
        SDL_FillRect(surface, NULL, skyblue);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
	return(0);
}
