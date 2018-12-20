#ifndef GameController_hpp
#define GameController_hpp

#include <iostream>
#include <memory>

#include "Game.hpp"
#include "GraphicsEngine.hpp"
#include "EventManager.hpp"

#include <cmath>

class GameController: Events::QuitEventObserver, Events::KeyboardEventObserver, Events::MouseEventObserver {

private:
    // when false, cleans the memory and close the game.
    bool m_isRunning = true;
    bool m_isDebugGridActive = false;

    const int m_CHUNK_FRAME_DURATION = 60;
    int m_chunkframe = 0;


    // contains all keycodes of currently pressed keyboard keys
    //DEPRECATED

    // player point of view, scene camera.
    GraphicsEngine::Camera m_playerPointOfView;

    std::unique_ptr<Game> m_currentGame;

    std::shared_ptr<GraphicsEngine::Object3D> m_debugGrid;
    std::shared_ptr<GraphicsEngine::Object3D> m_skybox;

    static std::shared_ptr<GraphicsEngine::Object3D> initializeDebugGrid();
    static std::shared_ptr<GraphicsEngine::Object3D> createSkyBox();

    void initializeScene();


    // EVENT OBSERVERS

    // observer method called by the event manager
    // when called, sets the running condition returned by loop to false.
    void quitEventHandler() override;

    // observer methods called by the event manager when a key is engaged
    // Add/Removes the pressed key from the pressedKeys set.
    void keyRealeaseHandler(unsigned char keycode) override;
    void keyPressHandler(std::set<unsigned char> &pressedKeys) override;

    // observer methods called by the event manager when a mouse event is fired
    // controls the camera orientation
    void mouseMoveHandler(float relativeXMovement,float relativeYMovement) override;
    // controls the camera position (x-z plane)
    void mouseWheelHandler(float deltaX, float deltaY) override;
    // captures the cursor in the sdl window
    void mouseReleaseHandler(unsigned char button) override;



    // private constructor
    GameController();

    // singleton instances
    static GameController*  s_controllerInstance;

public:

    //  launches the game (prepare frameworks, opens window)
    void setup();

    // Game loop, return false when exiting the program.
    bool loop();

    // singleton getter
    static GameController* instance();

    // destructor
    ~GameController() {}
};

#endif /* GameController_hpp */
