//
//  SDL_manager.hpp
//  Project Pasteque
//
//  Created by Pierre Gabory on 15/11/2018.
//

#ifndef SDL_manager_hpp
#define SDL_manager_hpp

#include <iostream>
#include <vector>

#include "Frameworks.hpp"
#include "Exceptions.hpp"
#include "Window.hpp"
#include "Scene.hpp"

namespace GraphicsEngine {
    class Controller {
    private:
        Window *window;
        Scene *currentScene;
        
        void initialize();
        void initializeGlew(Window window);
        
    public:
        void setup();
        
        void draw();
        
        void pollEvents();
        
        void printInfos();
        
        void close();
        
        void addObjectToCurrentScene(Object *newObject);
    };
}

#endif /* SDL_manager_hpp */
