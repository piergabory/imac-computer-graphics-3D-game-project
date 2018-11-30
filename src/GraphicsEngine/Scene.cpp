/**
 * Scene.cpp
 */

#include "Scene.hpp"

namespace GraphicsEngine
{
    // set camera to fov 70,  4:3 aspect,  and x1000 zbuffer sampling
    Scene::Scene(): camera(70.f, 800.f/600.f, 0.1f, 100.f) {
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
        for(std::vector<Object*>::const_iterator objectPtr = m_objects.begin(); objectPtr != m_objects.end(); ++objectPtr) {
            // update the shader's matrices
            (*objectPtr)->project(camera.projectionMatrix());
            
            // push the vertices in the pipeline
            (*objectPtr)->draw();
        }
    }
}
