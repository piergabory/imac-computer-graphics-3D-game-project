/**
 * Scene.cpp
 */

#include "Scene.hpp"

namespace GraphicsEngine
{
    // set camera to fov 70,  4:3 aspect,  and x1000 zbuffer sampling
    Scene::Scene(): m_camera(new Camera()) {
    }

    Scene::Scene(Camera* cameraPtr): m_camera(cameraPtr) {
    }
    
    Scene::~Scene()
    {}
    
    
    void Scene::add(std::shared_ptr<Object> &newObject)
    {
        m_objects.push_back(newObject);
        newObject->setProjection(m_camera->projectionMatrix(), m_camera->modelMatrix());
        // shared pointer is destroyed.
        // Value is own in the scope of Scene::add() call, and linked here by a weak pointer in m_objects
    }
    
    
    void Scene::render()
    {
        for(std::vector< std::weak_ptr<Object> >::iterator objectIterator = m_objects.begin(); objectIterator != m_objects.end(); ++objectIterator) {
            if (objectIterator->expired()) {
                //m_objects.erase(objectIterator);
                continue;
            }

            std::shared_ptr<Object> object = objectIterator->lock();

            // update the shader's matrices
            object->project();
            
            // push the vertices in the pipeline
            object->draw();

        }

        // shared pointer object is destroyed.
    }
}
