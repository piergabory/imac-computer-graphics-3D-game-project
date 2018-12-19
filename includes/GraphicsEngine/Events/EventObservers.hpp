/**
 * EventObservers.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef EventObservers_hpp
#define EventObservers_hpp

#include <set>

// EVENT OBSERVERS

/**
 * QuitEventObserver Interface
 *
 * Classes implementing this interface can
 * subscribe to window event in EventManager
 */
struct QuitEventObserver {
    // handles user request to quit the application
    virtual void quitEventHandler() = 0;

    // handles window event (resize/move)
    virtual void windowEventHandler() {};
};



/**
 * KeyboardEventObserver Interface
 *
 * Classes implementing this interface can
 * subscribe to key events in EventManager
 */
struct KeyboardEventObserver {
    // handles a key release from the user
    virtual void keyRealeaseHandler(unsigned char keycode) {}
    // handles a key press from the user
    virtual void keyDownHandler(unsigned char keycode) {}
    // handles a set of keys
    virtual void keyPressHandler(std::set<unsigned char> pressedKeys){}
};



/**
 * MouseEventObserver Interface
 *
 * Classes implementing this interface can
 * subscribe to mouse events in EventManager
 */
struct MouseEventObserver {
    // handles a mouse release from the user
    virtual void mouseReleaseHandler(unsigned char button) {}

    // handles a mouse down from the user
    virtual void mouseDownHandler(unsigned char button) {}

    // handles a mouse movement from the user
    virtual void mouseMoveHandler(float relativeXMovement,float relativeYMovement) {}

    // handles scrollwheel
    virtual void mouseWheelHandler(float deltaX, float deltaY) {}
};

#endif /* EventObservers_hpp */
