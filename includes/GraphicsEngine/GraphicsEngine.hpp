//
//  SDL_manager.hpp
//  Project Pasteque
//
//  Created by Pierre Gabory on 15/11/2018.
//

#ifndef SDL_manager_hpp
#define SDL_manager_hpp

#include <iostream>
#include <stack>

#include "Frameworks.hpp"
#include "Exceptions.hpp"
#include "Window.hpp"
#include "Object.hpp"

namespace GraphicsEngine {
    
    static Window *window;
    static std::stack<Object> objectsToBeDrawn;
    
    void setup();
    
    void draw();
    
    void pollEvents();
    
    void printInfos();
    
    void close();
}


/*


class SDLManager {
    
private:
    static SDLManager* m_instance;
    
    SDL_Window *window;
    SDL_GLContext glContext;
    
    uint m_width;
    uint m_height;
    
    SDLManager() {}
    ~SDLManager() {}
    
    
    
public:
    static SDLManager* Instance();
    
    void initialize();
    void createWindow(uint width, uint height, const char* title);
    void updateWindow(uint width, uint height);
    void setGlew();
    void printGlewInfo();
    
    inline uint getViewportWidth() { return m_instance->m_width; }
    inline uint getViewportHeight() { return m_instance->m_height; }
    inline void close();
    
};





class SDLManagerException : std::exception {
    
private:
    const std::string m_message;
    const std::string m_SDL_error;
    
public:
    inline const char* what() const throw() override {
        return ("SDM MANAGER EXCEPTION: " + m_message + " -> " + m_SDL_error).c_str();
    }
    
    SDLManagerException(const char* message, const char* sdl) :
        m_message(message), m_SDL_error(sdl)
        {}
    
    SDLManagerException(const char* message, unsigned const char* sdl) :
        m_message(message), m_SDL_error(reinterpret_cast<const char*>(sdl))
        {}
    
    ~SDLManagerException() override {}
};*/

#endif /* SDL_manager_hpp */
