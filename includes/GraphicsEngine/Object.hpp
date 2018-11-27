//
//  Object.hpp
//  product
//
//  Created by Pierre Gabory on 17/11/2018.
//

#ifndef Object_hpp
#define Object_hpp

#include <vector>

#include "CommonStructs.hpp"
#include "Frameworks.hpp"

namespace GraphicsEngine
{
    
    class Object
    {
    private:
        GLuint m_vertexBufferObject;
        GLuint m_vertexArrayObject;
        const int m_vertexCount;
        
        void setVertexArray(const std::vector<Vertex> &vertices) const;
        
        void setVertexBuffer(const std::vector<Vertex> &vertices) const;
        
    public:
        Object(): m_vertexBufferObject(0), m_vertexArrayObject(0), m_vertexCount(0) {};
        Object(const std::vector<Vertex> &vertices);
        ~Object();
        
        inline GLuint vertexArrayIdentifier() const {
            return m_vertexArrayObject;
        }
        
        inline const int vertexCount() const  {
            return m_vertexCount;
        }
    };
}

#endif /* Object_hpp */
