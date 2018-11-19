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
        int m_vertexCount;
        
        enum VertexAttributesIndices
        {
            VERTEX_ATTR_POSITION,
            VERTEX_ATTR_NORMAL,
            VERTEX_ATTR_TEXTURE
        };
        
    public:
        Object(): m_vertexBufferObject(0), m_vertexArrayObject(0), m_vertexCount(0) {};
        Object(std::vector<Vertex> vertices);
        ~Object();
        
        inline GLuint vertexArrayIdentifier() const {
            return m_vertexArrayObject;
        }
        
        inline int vertexCount() const  {
            return m_vertexCount;
        }
    };
}

#endif /* Object_hpp */
