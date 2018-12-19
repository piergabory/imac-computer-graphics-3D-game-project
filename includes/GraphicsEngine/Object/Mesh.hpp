/**
 * \file Mesh.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>

#include "CommonStructs.hpp"
#include "Frameworks.hpp"

namespace GraphicsEngine {


    /**
     * MESH TEMPLATE CLASS
     * \version 0.3
     *
     * \brief Manages and Loads in GPU a group of vertices.
     * \warning Use Mesh3D or Mesh2D Aliases!
     */
    template<class VertexType>
    class Mesh {

    private:
        /// \brief opengGl objects refrences
        GLuint m_vertexBufferObject;
        GLuint m_vertexArrayObject;
        
        
        /// \brief mesh vertices count
        const GLsizei m_vertexCount;

        /// \brief Indicates the drawing mode
        // TRIANGLE, LINE, POINT, TRIANGLE_FAN
        const GLenum m_glArrayDrawMode;
        
        /// \brief create vertex buffer
        void setVertexBuffer(const std::vector<VertexType> &vertices) const {
            // select buffer
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
            // push data in buffer
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType), vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        
        /// \brief construct vertex Array from vertex Buffer
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


        inline const GLsizei vertexCount() const  {
            return m_vertexCount;
        }


        inline const GLenum mode() const {
            return m_glArrayDrawMode;
        }
    };

    /// aliases
    using Mesh3D = Mesh<Vertex3D>;
    using Mesh2D = Mesh<Vertex2D>;
}

#endif /* Mesh_hpp */
