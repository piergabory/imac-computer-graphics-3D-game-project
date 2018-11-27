//
//  Object.cpp
//  product
//
//  Created by Pierre Gabory on 17/11/2018.
//

#include "Object.hpp"

namespace GraphicsEngine
{
    
    void Object::setVertexArray(const std::vector<Vertex> &vertices) const {
        enum { VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXTURE };
        
        glBindVertexArray(m_vertexArrayObject);
        
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(vertices[0].m_position));
        glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(vertices[0].m_normal));
        glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(vertices[0].m_textureCoordinates));
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    
    
    void Object::setVertexBuffer(const std::vector<Vertex> &vertices) const {
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    
    
    Object::Object(const std::vector<Vertex> &vertices):
    m_vertexCount((int) vertices.size())
    {
        glGenBuffers(1, &m_vertexBufferObject);
        setVertexBuffer(vertices);
        
        glGenVertexArrays(1, &m_vertexArrayObject);
        setVertexArray(vertices);
    }
    
    
    
    Object::~Object() {
        glDeleteBuffers(1, &m_vertexBufferObject);
        glDeleteVertexArrays(1, &m_vertexArrayObject);
    }
    
}
