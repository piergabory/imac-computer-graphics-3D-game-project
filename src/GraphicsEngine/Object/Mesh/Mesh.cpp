/**
 * \file Mesh.cpp
 */

#include "Mesh.hpp"

namespace GraphicsEngine {

    template<>
    void Mesh<Vertex3D>::setVertexArray(const std::vector<Vertex3D> &vertices) const {
        
        // layer ids (0,1,2..)
        enum {
            VERTEX_ATTR_POSITION,
            VERTEX_ATTR_NORMAL,
            VERTEX_ATTR_TEXTURE
        };
        
        // select vao
        glBindVertexArray(m_vertexArrayObject);
        
        // enable layers
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        
        // select vbo
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        
        // read in vbo -> set vao
        /**
         * params:
         * 1: Layer id
         * 2: vector size
         * 3: vector type
         * 4: ???
         * 5: vertex size in vbo
         * 6: location of the vector relative to each vertex
         *
         * in memory vertex are Vertex: [3Dvector position, 3Dvector normal, 2Dvector UVcoords]
         */
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), 0);
        
        glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const void*) (1 * sizeof(glm::vec3)));
        
        glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),  (const void*) (2 * sizeof(glm::vec3)));
        
        // deselect vao/vbo
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        // clear buffer
        glDeleteBuffers(1, &m_vertexBufferObject);
    }



    template<>
    void Mesh<Vertex2D>::setVertexArray(const std::vector<Vertex2D> &vertices) const {

        // layer ids (0,1,2..)
        enum {
            VERTEX_ATTR_POSITION,
            VERTEX_ATTR_TEXTURE
        };

        // select vao
        glBindVertexArray(m_vertexArrayObject);

        // enable layers
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

        // select vbo
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

        // read in vbo -> set vao
        /**
         * params:
         * 1: Layer id
         * 2: vector size
         * 3: vector type
         * 4: ???
         * 5: vertex size in vbo
         * 6: location of the vector relative to each vertex
         *
         * in memory vertex are Vertex: [3Dvector position, 3Dvector normal, 2Dvector UVcoords]
         */
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);

        glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),  (const void*) (1 * sizeof(glm::vec2)));

        // deselect vao/vbo
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // clear buffer
        glDeleteBuffers(1, &m_vertexBufferObject);
    }

}
