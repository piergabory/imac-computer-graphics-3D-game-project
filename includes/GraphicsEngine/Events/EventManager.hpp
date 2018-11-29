#ifndef EventManager_hpp
#define EventManager_hpp

#include "Frameworks.hpp"
#include "EventObservers.hpp"

namespace GraphicsEngine {
    class EventManager {
    private:
        static EventManager* m_pEventManagerInstance;
        
        QuitEventObserver* m_pQuitEventObserver;
        MouseEventObserver* m_pMouseEventsObserver;
        KeyboardEventObserver* m_pKeyboardEventsObserver;
        
    public:
        static EventManager* instance();
        
        void pollEvents() const;
        
        void subscribe(QuitEventObserver* quitObserver);
        void subscribe(MouseEventObserver* mouseObserver);
        void subscribe(KeyboardEventObserver* keyboardObserver);
    };
}

#endif /* EventManager_hpp */
