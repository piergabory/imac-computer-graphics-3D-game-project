/**
 * EventManager.hpp
 *
 * IMAC 2 Project CG CPP
  * \version 0.2
 * \brief gestion des évenements
 *
 * Version 0.2: Contient des tableau d'observer, plusieurs objets peuvent maintenant écouter les évènements
 */
#ifndef EventManager_hpp
#define EventManager_hpp

#include <vector>
#include <memory>
#include <set>

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
        ///< Les observeurs sont contenus dans des vectors de pointeurs (unique_ptr)
        std::vector<std::unique_ptr<QuitEventObserver> >  m_pQuitEventObserver;
        std::vector<std::unique_ptr<MouseEventObserver> > m_pMouseEventsObserver;
        std::vector<std::unique_ptr<KeyboardEventObserver> > m_pKeyboardEventsObserver;

        // contains all keycodes of currently pressed keyboard keys
        std::set<unsigned char> m_pressedKeys;

        void insertInSet(unsigned char key){
          m_pressedKeys.insert(key);
        }

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
