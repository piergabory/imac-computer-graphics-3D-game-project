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
        
        // create vertex buffer
        void setVertexBuffer(const std::vector<Vertex> &vertices) const;
        
        // construct vertex Array from vertex Buffer
        void setVertexArray(const std::vector<Vertex> &vertices) const;
        
        
    public:
        // constructor
        Mesh(const std::vector<Vertex> &vertices);
        
        // destrucor
        ~Mesh();
        
        
        // getters        
        inline const GLuint &vertexArrayIdentifier() const {
            return m_vertexArrayObject;
        }
        
        
        inline const int vertexCount() const  {
            return m_vertexCount;
        }
    };
}

#endif /* Mesh_hpp */
