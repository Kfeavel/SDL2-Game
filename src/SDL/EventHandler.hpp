#pragma once
#include <array>
#include <vector>
#include <functional>
#include <SDL.h>
#include "../Logger/Logger.hpp"

namespace SDL
{

class EventHandler
{
public:
    static EventHandler& the()
    {
        static EventHandler eventLoop;
        return eventLoop;
    }

    void addEventHandler(std::function<void(SDL_Event& e)> eventHandler, SDL_EventType eventType)
    {
        m_eventHandlers[eventType].push_back(eventHandler);
    }

    std::vector<std::function<void(SDL_Event& e)>>& getEventHandlers(uint32_t eventType)
    {
        return m_eventHandlers[eventType];
    }

private:
    std::array<std::vector<std::function<void(SDL_Event& e)>>, SDL_LASTEVENT> m_eventHandlers;
};

}
