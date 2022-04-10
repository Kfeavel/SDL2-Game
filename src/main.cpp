#include "Logger/Logger.hpp"
#include <filesystem>
#include <cstdlib>
#include <SDL.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

static SDL_Window* gWindow = nullptr;
static SDL_Surface* gScreenSurface = nullptr;
static SDL_Surface* gHelloWorld = nullptr;

static bool Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::Fatal() << SDL_GetError() << std::endl;
        return false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            Logger::Fatal() << SDL_GetError() << std::endl;
            return false;
        }

        gScreenSurface = SDL_GetWindowSurface(gWindow);
    }

    Logger::Info() << "Initialized SDL" << std::endl;
    return true;
}

static bool LoadAssets()
{
    gHelloWorld = SDL_LoadBMP("assets/hello_world.bmp");
    if (gHelloWorld == nullptr) {
        Logger::Fatal() << SDL_GetError() << std::endl;
        return false;
    }

    Logger::Info() << "Loaded assets" << std::endl;
    return true;
}

static void Destroy()
{
    Logger::Info() << "Destroying engine..." << std::endl;
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    Logger::Info() << "cwd: " << std::filesystem::current_path() << std::endl;

    bool quit = false;
    if (Initialize()) {
        if (LoadAssets()) {
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);

            // TODO: Move event loop elsewhere.
            // Event loop is required for macOS to display window
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
            }
        } else {
            Logger::Fatal() << "Failed to load all assets" << std::endl;
            return EXIT_FAILURE;
        }
    } else {
        Logger::Fatal() << "Failed to initialize" << std::endl;
        return EXIT_FAILURE;
    }

    Destroy();
    return EXIT_SUCCESS;
}
