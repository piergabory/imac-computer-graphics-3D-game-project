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

    bool m_isDebugGridActive = false;

    // contains all keycodes of currently pressed keyboard keys
    std::set<unsigned char> m_pressedKeys;

    // player point of view, scene camera.
    GraphicsEngine::Camera m_playerPointOfView;

    std::shared_ptr<GraphicsEngine::Object3D> m_debugGrid;
    std::shared_ptr<GraphicsEngine::Object3D> m_helloTriangle;

    void handlePressedKey();

    void linkEventObserver();

    void initializeScene();

    void createObjects();

    // private constructor
    GameController();

    // singleton instances
    static GameController*  m_controllerInstance;

public:

    //  launches the game (prepare frameworks, opens window)
    void setup();

    // Game loop, return false when exiting the program.
    bool loop();

    // observer method called by the event manager
    // when called, sets the running condition returned by loop to false.
    void quitEventHandler() override;

    // observer methods called by the event manager when a key is engaged
    // Add/Removes the pressed key from the pressedKeys set.
    void keyDownHandler(unsigned char keycode) override;
    void keyRealeaseHandler(unsigned char keycode) override;


    // observer methods called by the event manager when a mouse event is fired
    // controls the camera orientation
    void mouseMoveHandler(float relativeXMovement,float relativeYMovement) override;
    // controls the camera position (x-z plane)
    void mouseWheelHandler(float deltaX, float deltaY) override;
    // captures the cursor in the sdl window
    void mouseReleaseHandler(unsigned char button) override;

    // singleton getter
    static GameController* instance();

    // destructor
    ~GameController() {}
};

#endif /* GameController_hpp */
