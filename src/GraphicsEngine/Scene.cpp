/**
 * Scene.cpp
 */

#include "Scene.hpp"

namespace GraphicsEngine
{
    // set camera to fov 70,  4:3 aspect,  and x1000 zbuffer sampling
    Scene::Scene(): m_camera(new Camera()) {}

    Scene::Scene(Camera &camera): m_camera(std::make_shared<Camera>(camera)) {}
    
    Scene::~Scene() {}
    
    
    void Scene::add(std::shared_ptr<Object> &newObject)
    {
        m_objects.push_back(newObject);
        newObject->setProjection(m_camera->projectionMatrix(), m_camera->modelMatrix());
        // shared pointer is destroyed.
        // Value is own in the scope of Scene::add() call, and linked here by a weak pointer in m_objects
    }


    void Scene::remove(std::shared_ptr<Object> &object) {
        for(size_t i = 0; i < m_objects.size(); ++i) {
            std::shared_ptr<Object> tmpobject = m_objects[i].lock();

            // find object and deletes it.
            if (object == tmpobject) {
                m_objects.erase(m_objects.begin() + i);
            }
            
            // tmpobject is destroyed
        }
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