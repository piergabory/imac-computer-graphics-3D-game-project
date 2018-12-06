/**
 * Scene.cpp
 */

#include "Scene.hpp"

namespace GraphicsEngine
{
    // set camera to fov 70,  4:3 aspect,  and x1000 zbuffer sampling
    Scene::Scene(): m_camera(new Camera(70.f, 800.f/600.f, 0.1f, 100.f)) {
    }

    Scene::Scene(Camera* cameraPtr): m_camera(cameraPtr) {
    }
    
    Scene::~Scene()
    {
        // iterates through each object pointer
        for(std::vector<Object*>::const_iterator object = m_objects.begin(); object != m_objects.end(); ++object)
            delete *object;
    }
    
    
    void Scene::add(Object *newObject)
    {
        m_objects.push_back(newObject);
    }
    
    
    void Scene::render() const
    {
        for(Object* object : m_objects) {
            // update the shader's matrices
            object->project(m_camera->projectionMatrix());
            
            // push the vertices in the pipeline
            object->draw();
        }
    }
}
