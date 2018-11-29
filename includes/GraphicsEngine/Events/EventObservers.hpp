#ifndef EventObservers_hpp
#define EventObservers_hpp

struct QuitEventObserver {
    virtual void quitEventHandler() = 0;
    virtual void windowEventHandler() {};
};

struct KeyboardEventObserver {
    virtual void keyRealeaseHandler(unsigned char keycode) {};
    virtual void keyDownHandler(unsigned char keycode) {};
};

struct MouseEventObserver {
    virtual void mouseReleaseHandler(unsigned char button) {};
    virtual void mouseDownHandler(unsigned char button) {};
    virtual void mouseMoveHandler(float relativeXMovement,float relativeYMovement) {};
};

#endif /* EventObservers_hpp */
