#ifndef GameController_hpp
#define GameController_hpp

#include <iostream>
#include <set>
#include <memory>

#include "GraphicsEngine.hpp"
#include "EventObservers.hpp"

class GameController: QuitEventObserver, KeyboardEventObserver, MouseEventObserver {

private:
    // when false, cleans the memory and close the game.
    bool m_isRunning = true;

    // contains all keycodes of currently pressed keyboard keys
    std::set<unsigned char> m_pressedKeys;

    // player point of view, scene camera.
    GraphicsEngine::Camera m_playerPointOfView;

    void handlePressedKey();

    void linkEventObserver();

    void initializeScene();

    // private constructor
    GameController() {}

    // singleton instances
    static GameController*  m_controllerInstance;

public:

    void setup();

    bool loop();

    void quitEventHandler() override;

    void keyRealeaseHandler(unsigned char keycode) override;

    void keyDownHandler(unsigned char keycode) override;

    void mouseMoveHandler(float relativeXMovement,float relativeYMovement) override;
    void mouseWheelHandler(float deltaX, float deltaY) override;
    void mouseReleaseHandler(unsigned char button) override;

    // singleton getter
    static GameController* instance();

    // destructor
    ~GameController() {}
};

#endif /* GameController_hpp */
