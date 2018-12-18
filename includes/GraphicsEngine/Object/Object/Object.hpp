//
//  Object.hpp
//  Projet_S2_CG_CPP
//
//  Created by Pierre Gabory on 17/12/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include <memory>

#include "Mesh.hpp"
#include "Material.hpp"

namespace GraphicsEngine {

    template<class VertexType>
    class Object {
        
    protected:
        // Mesh, represent the group of vertices making the shape of the object.
        // (Vertex Array Object)
        std::shared_ptr< Mesh<VertexType> > m_mesh;

        // Material, represent the object behavior with light (Shaders and textures)
        std::shared_ptr<Material> m_material;

    public:

        // apply material and push the mesh vertices in the graphic pipeline
        void draw() const {
            glBindVertexArray(m_mesh->vertexArrayIdentifier());
            m_material->apply();

            glDrawArrays(m_mesh->mode(), 0, m_mesh->vertexCount());

            glBindTexture(GL_TEXTURE_2D, 0);
            glBindVertexArray(0);

        }

        /**
         * constructor
         * initialise mesh and material. Assumes that both are not NULL pointers
         */
        Object(std::shared_ptr< Mesh<VertexType> > mesh, std::shared_ptr<Material> material) : m_mesh(mesh), m_material(material) {
            assert(mesh != nullptr);
            assert(material != nullptr);
        }

        // destructor
        ~Object() {}
    };

}

#endif /* Object_h */
