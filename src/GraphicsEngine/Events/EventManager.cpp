#include "EventManager.hpp"

namespace GraphicsEngine {
    EventManager* EventManager::m_pEventManagerInstance = nullptr;
    
    EventManager* EventManager::instance() {
        if (m_pEventManagerInstance == nullptr)
            m_pEventManagerInstance = new EventManager();
        return  m_pEventManagerInstance;
    }
    
    void EventManager::pollEvents() const {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            
            if (m_pQuitEventObserver) switch (event.type) {
                case SDL_QUIT: m_pQuitEventObserver->quitEventHandler(); break;
                case SDL_WINDOWEVENT: m_pQuitEventObserver->windowEventHandler(); break;
                default: break;
            }
            
            if (m_pMouseEventsObserver) switch (event.type) {
                case SDL_MOUSEMOTION: m_pMouseEventsObserver->mouseMoveHandler(event.motion.xrel,event.motion.yrel); break;
                case SDL_MOUSEBUTTONDOWN: m_pMouseEventsObserver->mouseDownHandler(event.button.button); break;
                case SDL_MOUSEBUTTONUP: m_pMouseEventsObserver->mouseReleaseHandler(event.button.button); break;
                default: break;
            }
            
            if (m_pKeyboardEventsObserver) switch (event.type) {
                case SDL_KEYDOWN: m_pKeyboardEventsObserver->keyDownHandler(event.key.keysym.sym); break;
                case SDL_KEYUP: m_pKeyboardEventsObserver->keyRealeaseHandler(event.key.keysym.sym); break;
                default: break;
            }
        }
    }
    
    void EventManager::subscribe(QuitEventObserver* quitObserver) {
        m_pQuitEventObserver = quitObserver;
    }
    
    void EventManager::subscribe(MouseEventObserver* mouseObserver) {
        m_pMouseEventsObserver = mouseObserver;
    }
    
    void EventManager::subscribe(KeyboardEventObserver* keyboardObserver) {
        m_pKeyboardEventsObserver = keyboardObserver;
    }
}
