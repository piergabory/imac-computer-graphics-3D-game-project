#include "EventManager.hpp"

namespace GraphicsEngine {
    // define instance in cpp file
    EventManager* EventManager::m_pEventManagerInstance = nullptr;
    
    // singleton instance getter
    EventManager* EventManager::instance() {
        // creates instance if doesn't exists
        if (m_pEventManagerInstance == nullptr)
            m_pEventManagerInstance = new EventManager();
        
        return  m_pEventManagerInstance;
    }
    
    
    void EventManager::pollEvents() const {
        // temporary variable holding each event
        SDL_Event event;
        
        // fetches every event until there's none left
        while (SDL_PollEvent(&event)) {
            
            // check if observer is defined
            if (m_pQuitEventObserver) {
                // check event type, calls the corresponding method.
                switch (event.type) {
                    case SDL_QUIT: m_pQuitEventObserver->quitEventHandler(); break;
                    case SDL_WINDOWEVENT: m_pQuitEventObserver->windowEventHandler(); break;
                    default: break;
                }
            }
            
            if (m_pMouseEventsObserver) {
                switch (event.type) {
                    case SDL_MOUSEMOTION: m_pMouseEventsObserver->mouseMoveHandler(event.motion.xrel,event.motion.yrel); break;
                    case SDL_MOUSEBUTTONDOWN: m_pMouseEventsObserver->mouseDownHandler(event.button.button); break;
                    case SDL_MOUSEBUTTONUP: m_pMouseEventsObserver->mouseReleaseHandler(event.button.button); break;
                    default: break;
                }
            }
            
            if (m_pKeyboardEventsObserver) {
                switch (event.type) {
                    case SDL_KEYDOWN: m_pKeyboardEventsObserver->keyDownHandler(event.key.keysym.sym); break;
                    case SDL_KEYUP: m_pKeyboardEventsObserver->keyRealeaseHandler(event.key.keysym.sym); break;
                    default: break;
                }
            }
        }
    }
    
    
    
    // setters
    
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
