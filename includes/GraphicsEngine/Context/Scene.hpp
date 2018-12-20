/**
 * Scene.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Scene_hpp
#define Scene_hpp

#include "Object3D.hpp"
#include "Camera.hpp"
#include "Context.hpp"

/**
 * SCENE CLASS
 *
 * Contains and manages the camera, objects and lights.
 * Has ADD methods to populate the scene
 * Has a DRAW method to project the scene on the camera.
 */

namespace GraphicsEngine
{
    
    class Scene : public Context<Object3D> {
    
    private:
        /// Camera
        std::shared_ptr<Camera> m_camera;
        //light
        std::vector<std::weak_ptr<Light> > m_lights;


        void contextWillRender() const override {
            // hide faces viewed from behind
            glFrontFace(GL_CCW);
            glCullFace(GL_BACK);
            glEnable(GL_CULL_FACE);

            // enable z-buffer test
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
        }

        void initializeObject(Object3D &newObject) const override {
            newObject.setProjection(m_camera->projectionMatrix(), m_camera->modelMatrix());
        }


        void objectPrerenderStage(Object3D &newObject) const override {
            newObject.project();
        }


    public:
        
        // constructor
        // initialize camera
        Scene() : Context<Object3D>(), m_camera(std::make_shared<Camera>()) {}
        // takes an existing camera
        Scene(Camera &cameraPtr) : Context<Object3D>(), m_camera(std::make_shared<Camera>(cameraPtr)) {}

        // destructor
        // deletes memory allocated on each pointer in the object vector.
        ~Scene() {}
        /**
         * \brief add new light to the scene
         * @param newLight pointer that wil be destroyed
         */
        void addLight(std::shared_ptr<Light> &newLight){
            m_lights.push_back(newLight);
            // shared pointer is destroyed.
            // Value is own in the scope of Context::add() call, and linked here by a weak pointer in m_objects
        }
        /**
         * \brief remoove the light from the scene
         */
        void remooveLight(std::shared_ptr<Light> &light){
            for(size_t i = 0; i < m_lights.size(); ++i) {
                std::shared_ptr<Light> tmpobject = m_lights[i].lock();

                // find object and deletes it.
                if (light == tmpobject) {
                    m_lights.erase(m_lights.begin() + i);
                }

                // tmpobject is destroyed
            }
        }
    };
    
}

#endif /* Scene_hpp */
