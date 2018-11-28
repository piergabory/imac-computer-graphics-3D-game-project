//
//  SDL_manager.cpp
//  Project Pasteque
//
//  Created by Pierre Gabory on 15/11/2018.
//

#include "GraphicsEngine.hpp"

namespace GraphicsEngine {
    
    void Controller::initialize() {
        // initialisation de SDL
        if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
            throw InitialisationException("Failed to initialize SDL.", SDL_GetError());
        }
        
        // get the right OpenGL version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    }
    
    void Controller::initializeGlew(Window window) {
        // #ifndef __APPLE__
        glewExperimental = GL_TRUE;
        GLenum glewInitError = glewInit();
        if(glewInitError != GLEW_OK) {
            throw InitialisationException("Glew Initialisation failed.", reinterpret_cast<const char*>(glewGetErrorString(glewInitError)));
        }
        // #endif
    }
    
    void Controller::setup() {
        initialize();
        
        if (!window) {
            window = new Window();
            initializeGlew(*window);
        }
        
        delete currentScene;
        currentScene = new Scene();
    }
    
    void Controller::draw()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        currentScene->draw();
        window->swapBuffer();
    }
    
    void Controller::pollEvents()
    {
        SDL_PumpEvents();
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
        delete window;
    }
    
    void Controller::addObjectToCurrentScene(Object *newObject)
    {
        currentScene->add(newObject);
    }
}
