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
        Camera camera;
        
        
        /**
         * Object list in scene. Vector of object pointers.
         *
         * An object may appear twice, Objects know how to draw themselves.
         * Scene handle their relation with the camera's (aka, the projection matrix) for each of them on draw().
         */
        std::vector<Object*> m_objects;
        
        
        
    public:
        // adds an object in the scene.
        void add(Object *newObject);
        
        
        // Draws the scene: Span through each element in the scene, projects them on the camera.
        void render() const;
        
        
        // constructor
        // initialize camera
        Scene();
        
        
        // destructor
        // deletes memory allocated on each pointer in the object vector.
        ~Scene();
    };
    
}

#endif /* Scene_hpp */
