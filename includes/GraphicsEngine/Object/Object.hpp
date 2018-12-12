/**
 * Object.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Object_hpp
#define Object_hpp

#include "Frameworks.hpp"
#include "CommonStructs.hpp"
#include "Mesh.hpp"
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
        Mesh *m_mesh;
        
        // Material, represent the object behavior with light (Shaders and textures)
        // TODO: Allow multiple materials
        Material *m_material;
        
        // Model-View Matrix, represents the position/rotation/scale of the object in the scene.
        glm::mat4 m_modelViewMatrix;

      
        
    public:
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
        Object(Mesh *mesh, Material *material) : m_mesh(mesh), m_material(material) {
            assert(mesh != nullptr);
            assert(material != nullptr);
        }
        
        // alternate pointer free constructor
        Object(Mesh &mesh, Material &material) : m_mesh(&mesh), m_material(&material) {}

        // destructor
        ~Object() {}
    };
    
}

#endif /* Object_hpp */
