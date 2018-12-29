/**
 * Object.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Object_hpp
#define Object_hpp
#pragma once

#include <memory>

#include "Frameworks.hpp"
#include "CommonStructs.hpp"
#include "Mesh.hpp"
#include "ImportedMesh.hpp" //Remove this include (Debug for Imported Object)
#include "Material.hpp"

/**
 * OBJECT CLASS
 *
 * Join meshes and materials together.
 *
 * Proposes transformations methods to move around objects in the scene
 * has a draw methods that applies the material and push vertices in the pipeline.
 */

namespace GraphicsEngine {

    class Object {


    private:
        // Mesh, represent the group of vertices making the shape of the object.
        // (Vertex Array Object)
        std::shared_ptr<Mesh> m_mesh;

        // Material, represent the object behavior with light (Shaders and textures)
        std::shared_ptr<Material> m_material;

        // Model-View Matrix, represents the position/rotation/scale of the object in the scene.
        glm::mat4 m_modelViewMatrix;



    public:
        // link the scene camera's matrices to the perspectie shader.
        void setProjection(const std::shared_ptr<glm::mat4> &projectionMatrix, const std::shared_ptr<glm::mat4> &sceneModel);

        // apply a 3D translation on the object
        void translate(const glm::vec3 &translationVector);

        // apply a 3D rotation on the object
        void rotate(const float angle, const glm::vec3 &direction);

        // apply a 3D scale on the object
        void scale(const glm::vec3 &scalingVector);

        /**
        * ask the material to update the MVP Matrix and Normal Matrix in the shader.
        */
        void project();

        // apply material and push the mesh vertices in the graphic pipeline
        void draw() const;

        /**
         * constructor
         * initialise mesh and material. Assumes that both are not NULL pointers
         */
        Object(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : m_mesh(mesh), m_material(material) {
            assert(mesh != nullptr);
            assert(material != nullptr);
        }
        
        //TODO - Remove this constructor (debug)
        Object(std::shared_ptr<ImportedMesh> mesh, std::shared_ptr<Material> material) : m_mesh(mesh), m_material(material) {
            assert(mesh != nullptr);
            assert(material != nullptr);
        }

        Object(const Object &copy) = default;

        // destructor
        ~Object() {}
    };

}

#endif /* Object_hpp */
