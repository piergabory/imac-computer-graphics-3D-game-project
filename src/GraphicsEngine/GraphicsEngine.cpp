/**
 * Object.cpp
 */

#include "GraphicsEngine.hpp"

namespace GraphicsEngine {
    // singleton instance definition
    Controller* Controller::m_controllerInstance = nullptr;

    // singleton instance getter
    Controller* Controller::instance() {
        // create if non-existent
        if (Controller::m_controllerInstance == NULL)
            Controller::m_controllerInstance = new Controller();

        return Controller::m_controllerInstance;
    }


    // SDL Framework
    void Controller::initializeSDL() {
        // init and check
        if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
            throw InitialisationException("Failed to initialize SDL.", SDL_GetError());
        }
        
        // get the right OpenGL version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    }



    // GLEW Library
    // glew should not be necessary on macOs, but it works like that.
    void Controller::initializeGlew() {
        // #ifndef __APPLE__
        // glewExperimental = GL_TRUE;
        GLenum glewInitError = glewInit();
        if(glewInitError != GLEW_OK) {
            throw InitialisationException("Glew Initialisation failed.", reinterpret_cast<const char*>(glewGetErrorString(glewInitError)));
        }
        // #endif
    }


    // SDL Window init
    void Controller::initializeWindow(const char* windowTitle, const uint viewportWidth, const uint viewportHeight) {
        // open a window wherever the OS wants.
        // the window is resizable (=/= fullscreen) and uses opengl
        m_sdlWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, viewportWidth, viewportHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

        // check for success
        if (m_sdlWindow == nullptr)
            throw InitialisationException("Failed to create SDL window", SDL_GetError());

        // initialize OpenGL
        SDL_GL_CreateContext(m_sdlWindow);

        // hide faces viewed from behind
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);


        // enable z-buffer test
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }


    // setup
    void Controller::setup(const char* windowTitle, const uint viewportWidth, const uint viewportHeight) {

        initializeSDL();

        // create if windows doesn't exists
        if (!m_sdlWindow) {
            initializeWindow(windowTitle, viewportWidth, viewportHeight);
            initializeGlew();
        }
    }

    void Controller::loadScene(Scene* newScene) {
        assert(newScene);
        // destroy scene if already exists
        if (!m_activeScene)
            delete m_activeScene;
        m_activeScene = newScene;
    }

    void Controller::render()
    {
        // clears buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render the scene
        m_activeScene->render();

        // swap buffer width visible
        SDL_GL_SwapWindow(m_sdlWindow);
    }


    
    void Controller::pollEvents()
    {
        EventManager::instance()->pollEvents();
    }


    
    void Controller::printInfos()
    {
        std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
        // #ifndef __APPLE__
        std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
        // #endif
    }


    
    void Controller::close()
    {
        SDL_Quit();
        //delete window;
    }

}
