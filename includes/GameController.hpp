#ifndef GameController_hpp
#define GameController_hpp

#include <iostream>

#include "GraphicsEngine.hpp"
#include "EventObservers.hpp"

class GameController: QuitEventObserver, KeyboardEventObserver, MouseEventObserver {

private:
    bool m_isRunning = true;

    static GameController*  m_controllerInstance;

    GameController() {}

    void linkEventObserver();
    
    void initializeScene();

public:

    void setup();

    bool loop();

    void quitEventHandler() override;

    static GameController* instance();

    ~GameController() {}
};

#endif /* GameController_hpp */
