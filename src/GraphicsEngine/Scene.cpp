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
    Scene::~Scene()
    {
        for(size_t index = 0; index < m_objects.size(); ++index)
            delete m_objects[index];
    }
    
    
    void Scene::add(Object *newObject)
    {
        m_objects.push_back(newObject);
    }
    
    
    void Scene::draw() const
    {
        for(size_t index = 0; index < m_objects.size(); ++index)
        {
            glBindVertexArray(m_objects[index]->vertexArrayIdentifier());
            glDrawArrays(GL_TRIANGLES, 0, m_objects[index]->vertexCount());
        }
    }
}
