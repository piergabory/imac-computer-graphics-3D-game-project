/**
 * Scene.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Scene_hpp
#define Scene_hpp

#include <vector>
#include <iterator>
#include <memory>

#include "Object.hpp"
#include "Camera.hpp" 

/**
 * SCENE CLASS
 *
 * Contains and manages the camera, objects and lights.
 * Has ADD methods to populate the scene
 * Has a DRAW method to project the scene on the camera.
 */

namespace GraphicsEngine
{
    
    class Scene {
    
        
    private:
        /// Camera
        std::shared_ptr<Camera> m_camera;
        
        
        /**
         * Object list in scene. Vector of object pointers.
         *
         * An object may appear twice, Objects know how to draw themselves.
         * Scene handle their relation with the camera's (aka, the projection matrix) for each of them on draw().
         */
        std::vector< std::weak_ptr<Object> > m_objects;
        
        
        
    public:
        // adds an object in the scene.
        void add(std::shared_ptr<Object> &newObject);

        // remove an object from the scenes.
        void remove(std::shared_ptr<Object> &object);


        // Draws the scene: Span through each element in the scene, projects them on the camera.
        void render();
        
        
        // constructor
        // initialize camera
        Scene();
        // takes an existing camera
        Scene(Camera &cameraPtr);
        
        
        // destructor
        // deletes memory allocated on each pointer in the object vector.
        ~Scene();
    };
    
}

#endif /* Scene_hpp */
