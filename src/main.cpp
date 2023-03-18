#include "Logger/Logger.hpp"
#include "SDL/EventHandler.hpp"
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
        Logger::fatal() << SDL_GetError() << std::endl;
        return false;
    } else {
        gWindow = SDL_CreateWindow(
                "SDL Tutorial",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            Logger::fatal() << SDL_GetError() << std::endl;
            return false;
        }

        gScreenSurface = SDL_GetWindowSurface(gWindow);
    }

    Logger::info() << "Initialized SDL" << std::endl;
    return true;
}

static bool LoadAssets()
{
    gHelloWorld = SDL_LoadBMP("img/hello_world.bmp");
    if (gHelloWorld == nullptr) {
        Logger::fatal() << SDL_GetError() << std::endl;
        return false;
    }

    Logger::info() << "Loaded assets" << std::endl;
    return true;
}

static void EventLoop()
{
    while (true) {
        // While events are available to process
        static SDL_Event e;
        while (SDL_PollEvent(&e)) {
            auto handlers =  SDL::EventHandler::the().getEventHandlers(e.type);
            for (auto handler : handlers) {
                handler(e);
            }

            // Additional processing after passing off to events
            switch (e.type) {
                case SDL_QUIT:
                    Logger::trace() << "Quit event -- exiting event thread" << std::endl;
                    return;
            }
        }

        // TODO: Proper throttling
        SDL_Delay(50);
    }
}

static void Destroy(SDL_Event& e)
{
    (void)e;
    Logger::info() << "Destroying engine..." << std::endl;
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

    Logger::info() << "cwd: " << std::filesystem::current_path() << std::endl;
    Logger::info() << SDL_GetBasePath() << std::endl;

    if (Initialize()) {
        if (LoadAssets()) {
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);

            Logger::info() << "Adding SDL_QUIT event to event handler" << std::endl;
            SDL::EventHandler::the().addEventHandler(Destroy, SDL_QUIT);
            // Event loop *must* be handled by main thread or an exception will be thrown
            // This for sure applies to macOS but may apply to other hosts
            EventLoop();
        } else {
            Logger::fatal() << "Failed to load all assets" << std::endl;
            return EXIT_FAILURE;
        }
    } else {
        Logger::fatal() << "Failed to initialize" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
