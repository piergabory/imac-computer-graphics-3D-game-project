/**
 * Mesh.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>

#include "CommonStructs.hpp"
#include "Frameworks.hpp"

/**
 * MESH CLASS
 *
 * Manages and Loads in GPU, Vertices of objects.
 */

namespace GraphicsEngine {

    template<class VertexType>
    class Mesh {
        
    private:
        // gl objects
        GLuint m_vertexBufferObject;
        GLuint m_vertexArrayObject;
        
        
        // mesh vertices count
        const int m_vertexCount;

        // Indicates the drawing mode
        // TRIANGLE, LINE, POINT, TRIANGLE_FAN
        const GLenum m_glArrayDrawMode;
        
        // create vertex buffer
        void setVertexBuffer(const std::vector<VertexType> &vertices) const {
            // select buffer
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
            // push data in buffer
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType), vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        
        // construct vertex Array from vertex Buffer
        void setVertexArray(const std::vector<VertexType> &vertices) const;
        
        
    public:
        // constructor
        Mesh(const std::vector<VertexType> &vertices, const GLenum drawMode = GL_TRIANGLES) :
        m_vertexCount((int) vertices.size()),
        m_glArrayDrawMode(drawMode)
        {
            glGenBuffers(1, &m_vertexBufferObject);
            setVertexBuffer(vertices);

            glGenVertexArrays(1, &m_vertexArrayObject);
            setVertexArray(vertices);
        }
        
        // destrucor
        ~Mesh() {
            // clear VAO
            glDeleteVertexArrays(1, &m_vertexArrayObject);
        }
        
        
        // getters        
        inline const GLuint &vertexArrayIdentifier() const {
            return m_vertexArrayObject;
        }
        
        
        inline const int vertexCount() const  {
            return m_vertexCount;
        }

        inline const GLenum mode() const {
            return m_glArrayDrawMode;
        }
    };

    using Mesh3D = Mesh<Vertex3D>;
    using Mesh2D = Mesh<Vertex2D>;
}

#endif /* Mesh_hpp */
