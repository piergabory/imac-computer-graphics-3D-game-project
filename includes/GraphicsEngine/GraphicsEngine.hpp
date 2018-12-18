
/**
 * Object.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef GraphicEngine_hpp
#define GraphicEngine_hpp

#include <iostream>
#include <vector>
#include <memory>

#include "Exceptions.hpp"
#include "Scene.hpp"
#include "Canvas.hpp"
#include "EventManager.hpp"

/**
 * GRAPHIC ENGINE CONTROLLER CLASS
 *
 * Singleton, controller class of all things graphical
 * Initialize graphics frameworks, instanciate the window, launches event fetchs, launches scenes renders.
 */

namespace GraphicsEngine {
    
    class Controller {

    private:

        // sdl window struct pointer
        SDL_Window* m_sdlWindow;

        // current scene
        std::unique_ptr<Scene> m_activeScene;

        // curent
        std::unique_ptr<Canvas> m_activeGUI;

        // frameworks initializers
        void initializeSDL();
        void initializeGlew();
        // parameters: menu bar description, and the window's pixel dimentions
        void initializeWindow(const char* windowTitle, const uint viewportWidth, const uint viewportHeight);


        // singleton: private constructor
        Controller() {}

        // singleton instance
        static Controller* m_controllerInstance;


    public:
        
        // calls initializers for uninitialized frameworks
        void setup(const char* windowTitle = "", const uint viewportWidth = 800, const uint viewportHeight = 600);

        // replace existing scene with a given one
        void loadScene(std::unique_ptr<Scene> &newScene);

        // replace existing scene with a given one
        void loadGUI(std::unique_ptr<Canvas> &newGUI);

        // starts a render cycle
        void render();

        // calls events fetch to EventManager
        void pollEvents();

        // output miscellaneous infos, such as available frameworks versions.
        void printInfos();

        // closes the window with SDL_QUIT
        void close();


        // getters

        // singleton instance
        static Controller* instance();

        // scene
        inline const std::unique_ptr<Scene> &activeScene() const { return m_activeScene; }
        inline const std::unique_ptr<Canvas> &activeGUI() const { return m_activeGUI; }
    };
}

#endif /* GraphicEngine_hpp */
