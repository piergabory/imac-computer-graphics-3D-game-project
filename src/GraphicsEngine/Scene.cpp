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
    {
        // iterates through each object pointer
        for(Object* object : m_objects)
            delete object;
    }
    
    
    void Scene::add(Object *newObject)
    {
        m_objects.push_back(newObject);
        newObject->setProjection(m_camera->projectionMatrix(), m_camera->modelMatrix());
    }
    
    
    void Scene::render() const
    {
        for(Object* object : m_objects) {
            // update the shader's matrices
            object->project();
            
            // push the vertices in the pipeline
            object->draw();
        }
    }
}
