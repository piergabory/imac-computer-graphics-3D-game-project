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
        void setVertexBuffer(const std::vector<Vertex> &vertices) const;
        
        // construct vertex Array from vertex Buffer
        void setVertexArray(const std::vector<Vertex> &vertices) const;
        
        
    public:
        // constructor
        Mesh(const std::vector<Vertex> &vertices, const GLenum drawMode = GL_TRIANGLES);
        
        // destrucor
        ~Mesh();
        
        
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
}

#endif /* Mesh_hpp */
