/**
 * \file Scene.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Scene_hpp
#define Scene_hpp
#pragma once

#include "Object3D.hpp"
#include "Camera.hpp"
#include "Context.hpp"

namespace GraphicsEngine {
    
    /**
     * SCENE CLASS
     *
     * Context Sub-class
     * \brief Contains and manages the camera, objects and lights in a 3 dimensional space.
     */
    class Scene : public Context<Object3D> {
    
    private:
        /// Camera Instance
        std::shared_ptr<Camera> m_camera;

        // context Lifecycle
        /// \brief enables Backface Culling and and Depth testing (z-buffer)
        void contextWillRender() const override {
            // hide faces viewed from behind
            glFrontFace(GL_CCW);
            glCullFace(GL_BACK);
            glEnable(GL_CULL_FACE);

            // enable z-buffer test
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            
            // enable blending for gradient tansparency
            glDisable(GL_BLEND);
        }

        /// \brief links the camera projection and work model matrices to the object's perspective shader
        void initializeObject(const std::shared_ptr<Object3D> &newObject) const override {
            newObject->setProjection(m_camera->projectionMatrix(), m_camera->modelMatrix());
        }


        /// \brief calls the project method before each render
        /// the project method updates matrices uniforms
        void objectPrerenderStage(const std::shared_ptr<Object3D> &newObject) const override {
            newObject->project();
        }


    public:
        
        /// \brief constructors
        // initialize camera
        Scene() : Context<Object3D>(), m_camera(std::make_shared<Camera>()) {}

        // takes an existing camera
        Scene(Camera &camera) : Context<Object3D>(), m_camera(std::make_shared<Camera>(camera)) {}
        Scene(std::shared_ptr<Camera> &cameraPtr) : Context<Object3D>(), m_camera(cameraPtr) {}



        /// \brief destructor
        // deletes memory allocated on each pointer in the object vector.
        ~Scene() {}
    };
    
}

#endif /* Scene_hpp */
