/**
 * EventManager.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */
#ifndef EventManager_hpp
#define EventManager_hpp


#include "Frameworks.hpp"
#include "EventObservers.hpp"

/**
 * EVENT MANAGER CLASS
 *
 * Singleton class.
 * Manages events from the SDL framework. Calls the right observers.
 */
namespace GraphicsEngine {
    
    class EventManager {
    
    private:
        // singleton instance
        static EventManager* m_pEventManagerInstance;
        
        // observers
        // TODO: handle multiple observer per output
        QuitEventObserver* m_pQuitEventObserver;
        MouseEventObserver* m_pMouseEventsObserver;
        KeyboardEventObserver* m_pKeyboardEventsObserver;
        
    public:
        // instance getter
        static EventManager* instance();
        
        // fetches events from the SDL framework
        void pollEvents() const;
        
        // Add observer to the manager.
        void subscribe(QuitEventObserver* quitObserver);
        void subscribe(MouseEventObserver* mouseObserver);
        void subscribe(KeyboardEventObserver* keyboardObserver);
    
    };
    
}

#endif /* EventManager_hpp */
