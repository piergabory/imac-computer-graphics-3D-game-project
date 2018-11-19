//
//  SDL_manager.cpp
//  Project Pasteque
//
//  Created by Pierre Gabory on 15/11/2018.
//

#include "GraphicsEngine.hpp"

namespace GraphicsEngine {
    
    void initialize()
    {
        // initialisation de SDL
        if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
            throw Exception("Failed to initialize SDL.", SDL_GetError());
        }
        
        // get the right OpenGL version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    }
    
    void initializeGlew(Window window)
    {
        #ifndef __APPLE__
        glewExperimental = GL_TRUE;
        GLenum glewInitError = glewInit();
        if(glewInitError != GLEW_OK) {
            throw Exception("Glew Initialisation failed.", reinterpret_cast<const char*>(glewGetErrorString(glewInitError)));
        }
        #endif
    }
    
    void setup() {
        initialize();
        if (!window) {
            window = new Window();
            initializeGlew(*window);
        }
    }
    
    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        while (!objectsToBeDrawn.empty()) {
            Object* toDraw = &objectsToBeDrawn.top();
            
            glBindVertexArray(toDraw->vertexArrayIdentifier());
            glDrawArrays(GL_TRIANGLES, 0, toDraw->vertexCount());
            
            objectsToBeDrawn.pop();
        }
        
        GraphicsEngine::window->swapBuffer();
    }
    
    void pollEvents()
    {
        
    }
    
    void printInfos()
    {
        std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
        #ifndef __APPLE__
        std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
        #endif
    }
    
    void close()
    {
        SDL_Quit();
        delete window;
    }
}

/*
SDLManager* SDLManager::m_instance = nullptr;
SDLManager* SDLManager::Instance() {
    if (!m_instance)
        m_instance = new SDLManager();
    return m_instance;
}




void SDLManager::initialize() {

    // initialisation de SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        throw SDLManagerException("Failed to initialize SDL.", SDL_GetError());
    }
    
    // get the right OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
}




void SDLManager::setGlew() {
    assert(window);
    glewExperimental = GL_TRUE;
    GLenum glewInitError = glewInit();
    if(glewInitError != GLEW_OK) {
        throw SDLManagerException("Glew Initialisation failed.", glewGetErrorString(glewInitError));
    }
}




void SDLManager::printGlewInfo() {
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
}




void SDLManager::createWindow(uint width, uint height, const char* title) {
    m_width = width;
    m_width = height;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    
    if(window == nullptr) {
        throw SDLManagerException("Failed to initialize SDL.", SDL_GetError());
    }
    
    glContext = SDL_GL_CreateContext(window);
    
    updateWindow(width, height);
    
    m_instance->setGlew();
}




void SDLManager::updateWindow(uint width, uint height) {

}




void SDLManager::close() {
    SDL_Quit();
}
*/
