//
//  Scene.cpp
//  xcode target
//
//  Created by Pierre Gabory on 19/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#include "Scene.hpp"

namespace GraphicsEngine
{
    Scene::Scene(): camera(70.f,800.f/600.f, 0.1f, 100.f) {
    }
    
    
    Scene::~Scene()
    {
        for(std::vector<Object*>::const_iterator object = m_objects.begin(); object != m_objects.end(); ++object)
            delete *object;
    }
    
    
    void Scene::add(Object *newObject)
    {
        m_objects.push_back(newObject);
    }
    
    
    void Scene::draw() const
    {
        for(std::vector<Object*>::const_iterator objectPtr = m_objects.begin(); objectPtr != m_objects.end(); ++objectPtr) {
            (*objectPtr)->project(camera.projectionMatrix());
            (*objectPtr)->draw();
        }
        glBindVertexArray(0);
    }
}
