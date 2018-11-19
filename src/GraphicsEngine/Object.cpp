//
//  Object.cpp
//  product
//
//  Created by Pierre Gabory on 17/11/2018.
//

#include "Object.hpp"

namespace GraphicsEngine
{
    Object::Object(std::vector<Vertex> vertices):
    m_vertexCount((int) vertices.size())
    {
        glGenBuffers(1, &m_vertexBufferObject);
        glGenVertexArrays(1, &m_vertexArrayObject);
        
        glBindVertexArray(m_vertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(Object::VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(vertices.size()), 0);
        glVertexAttribPointer(Object::VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(vertices.size()), (const void*) (1 * sizeof(glm::vec3)));
        glVertexAttribPointer(Object::VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(vertices.size()), (const void*) (2 * sizeof(glm::vec3)));
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    Object::~Object() {
        glDeleteBuffers(1, &m_vertexBufferObject);
        glDeleteVertexArrays(1, &m_vertexArrayObject);
    }
    
}
