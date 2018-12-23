/**
 * \file GameController.hpp
 * 
 * IMAC 2 Project CG CPP
 */

#ifndef GameController_hpp
#define GameController_hpp

#include <iostream>
#include <memory>

#include "Game.hpp"
#include "GraphicsEngine.hpp"
#include "EventManager.hpp"
#include "Animation.hpp"

#include <cmath>


/**
 *
 * GAME CONTROLLER CLASS
 *
 * \brief Top of the class tree. Graphics engine facade. Contains Setup and game loop.
 *
 */

/// implements all event observers.
class GameController: Events::QuitEventObserver, Events::KeyboardEventObserver, Events::MouseEventObserver {

private:
    /// \brief when false, cleans the memory and close the game.
    bool m_isRunning = true;


    /// \brief defines the game rythm
    const int m_CHUNK_FRAME_DURATION = 60;
    int m_chunkframe = 0;


    /// \brief player point of view, scene camera.
    GraphicsEngine::Camera m_playerPointOfView;


    /// \brief object instances handles
    std::shared_ptr<GraphicsEngine::Object3D> m_debugGrid;
    std::shared_ptr<GraphicsEngine::Object3D> m_skybox;
    std::shared_ptr<GraphicsEngine::Object3D> m_chunk;


    // Model instance
    std::unique_ptr<Game> m_currentGame;


    // METHODS

    // setup
    void initializeScene();

    /// \brief static methods for object initialization
    /// Loading assets and shaders from relative filepaths to create a 3D object
    static std::shared_ptr<GraphicsEngine::Object3D> initializeDebugGrid();
    static std::shared_ptr<GraphicsEngine::Object3D> createSkyBox();
    static std::shared_ptr<GraphicsEngine::Object3D> createChunk();
    static std::shared_ptr<GraphicsEngine::Object3D> createObject3D(GraphicsEngine::LocalFilePath &meshPath, GraphicsEngine::LocalFilePath &textureImagePath,GraphicsEngine::LocalFilePath &vertexShaderPath, GraphicsEngine::LocalFilePath &fragmentShaderPath);



    // EVENT OBSERVERS

    /// \brief observer method called by the event manager
    /// when called, sets the running condition returned by loop to false.
    void quitEventHandler() override;

    /// \brief observer methods called by the event manager when a key is engaged
    /// Add/Removes the pressed key from the pressedKeys set.
    void keyRealeaseHandler(unsigned char keycode) override;
    void keyPressHandler(std::set<unsigned char> &pressedKeys) override;

    /// \brief observer methods called by the event manager when a mouse event is fired
    /// controls the camera orientation
    void mouseMoveHandler(float relativeXMovement,float relativeYMovement) override;
    /// controls the camera position (x-z plane)
    void mouseWheelHandler(float deltaX, float deltaY) override;
    /// captures the cursor in the sdl window
    void mouseReleaseHandler(unsigned char button) override;


    // STATICS

    /// \brief private singleton constructor
    GameController();

    /// \brief singleton instances
    static GameController*  s_controllerInstance;

public:

    /// \brief  launches the game (prepare frameworks, opens window)
    void setup();

    /// \brief Game loop, return false when exiting the program.
    bool loop();

    /// \brief singleton getter
    static GameController* instance();

    /// \brief destructor
    ~GameController() {}
};

#endif /* GameController_hpp */
