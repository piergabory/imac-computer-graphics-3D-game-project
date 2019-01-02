/**
 * \file Object.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */


#ifndef Object_h
#define Object_h
#pragma once

#include <memory>

#include "Mesh.hpp"
#include "Material.hpp"


namespace GraphicsEngine {

    /**
     * OBJECT TEMPLATE CLASS
     *
     * \brief Join meshes and materials together.
     * \version 0.3
     *
     * class matching a mesh and a material. proposes a Draw method binding the meshes and applying the material to then render the instance.
     * the mesh and material has to be defined
     */
    template<class VertexType>
    class Object {
        
    protected:
        /// \brief Mesh, represent the group of vertices making the shape of the object. (facade to OpenGL Vertex Array Object)
        std::shared_ptr< Mesh<VertexType> > m_mesh;

        /// \brief Material, represent the object behavior with light (wrapper of Shaders and textures)
        std::shared_ptr<Material> m_material;

    public:
        /// \brief apply material and push the mesh vertices in the graphic pipeline to be rendered
        void draw() const {
            // binds the mesh
            glBindVertexArray(m_mesh->vertexArrayIdentifier());

            // use the material
            m_material->apply();

            // render
            glDrawArrays(m_mesh->mode(), 0, m_mesh->vertexCount());
        }
        
        //change material of the object
        void material(std::shared_ptr<Material> mat){
            m_material = mat;
        }
        

        /// \brief Object constructor
        /// initialise mesh and material. Assumes that both are not NULL pointers 
        Object(std::shared_ptr< Mesh<VertexType> > mesh, std::shared_ptr<Material> material) : m_mesh(mesh), m_material(material) {
            assert(mesh != nullptr);
            assert(material != nullptr);
        }

        
        // destructor
        ~Object() {}

        std::string m_debug;
    };

}

#endif /* Object_h */
