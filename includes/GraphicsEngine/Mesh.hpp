//
//  mesh.hpp
//  product
//
//  Created by Pierre Gabory on 17/11/2018.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>

#include "CommonStructs.hpp"
#include "Frameworks.hpp"

namespace GraphicsEngine
{
    
    class Mesh {
    private:
        GLuint m_vertexBufferObject;
        GLuint m_vertexArrayObject;
        const int m_vertexCount;
        
        void setVertexArray(const std::vector<Vertex> &vertices) const;
        
        void setVertexBuffer(const std::vector<Vertex> &vertices) const;
        
    public:
        Mesh(): m_vertexBufferObject(0), m_vertexArrayObject(0), m_vertexCount(0) {};
        Mesh(const std::vector<Vertex> &vertices);
        ~Mesh();
        
        
        inline GLuint& vertexArrayIdentifier() {
            return m_vertexArrayObject;
        }
        
        
        inline GLuint vertexArrayIdentifier() const {
            return m_vertexArrayObject;
        }
        
        
        inline const int vertexCount() const  {
            return m_vertexCount;
        }
    };
}

#endif /* Mesh_hpp */
