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
    Scene::Scene() { }
    
    
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
            glBindVertexArray((*objectPtr)->vertexArrayIdentifier());
            glDrawArrays(GL_TRIANGLES, 0, (*objectPtr)->vertexCount());
        }
        glBindVertexArray(0);
    }
}
