/**
 * \file Object.cpp
 */

#include "GraphicsEngine.hpp"

namespace GraphicsEngine {
    // singleton instance definition
    Controller* Controller::s_controllerInstance = nullptr;

    // singleton instance getter
    Controller* Controller::instance() {
        // create if non-existent
        if (Controller::s_controllerInstance == nullptr)
            Controller::s_controllerInstance = new Controller();

        return Controller::s_controllerInstance;
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
    }


    // setup
    void Controller::setup(const char* windowTitle, const uint viewportWidth, const uint viewportHeight) {

        initializeSDL();

        // create if windows doesn't exists
        if (!m_sdlWindow) {
            initializeWindow(windowTitle, viewportWidth, viewportHeight);
            initializeGlew();
        }

        Object2D::initialize2DShaderProgram(LocalFilePath("shaders/2D.vs.glsl"), LocalFilePath("shaders/2D.fs.glsl"));
        Button::initializeButtons(viewportPixelSize());
    }

    void Controller::loadScene(std::unique_ptr<Scene> &newScene) {
        m_activeScene = std::move(newScene);
    }

    void Controller::loadGUI(std::unique_ptr<Canvas> &newGUI) {
        m_activeGUI = std::move(newGUI);
    }


    void Controller::render()
    {
        // clears buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // render the scene
        if (m_activeScene) m_activeScene->render();

        // print the GUI overlay
        if (m_activeGUI) m_activeGUI->render();

        // swap buffer width visible
        SDL_GL_SwapWindow(m_sdlWindow);
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


    inline const glm::ivec2 Controller::viewportPixelSize() const {
        int width, height;
        SDL_GetWindowSize(m_sdlWindow, &width, &height);
        return glm::ivec2(width, height);
    }

}
