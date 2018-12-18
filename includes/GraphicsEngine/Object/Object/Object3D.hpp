/**
 * Object.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Object_hpp
#define Object_hpp

#include "Object.hpp"
#include "PerspectiveShaderProgram.hpp"

/**
 * OBJECT CLASS
 *
 * Join meshes and materials together.
 *
 * Proposes transformations methods to move around objects in the scene
 * has a draw methods that applies the material and push vertices in the pipeline.
 */

namespace GraphicsEngine {
    
    class Object3D : public Object<Vertex3D> {

    private:
        // Model-View Matrix, represents the position/rotation/scale of the object in the scene.
        glm::mat4 m_modelViewMatrix;
        
    public:
        // apply a 3D translation on the object
        void translate(const glm::vec3 &translationVector);

        // apply a 3D rotation on the object
        void rotate(const float angle, const glm::vec3 &direction);

        // apply a 3D scale on the object
        void scale(const glm::vec3 &scalingVector);


        // link the scene camera's matrices to the perspectie shader.
        void setProjection(const std::shared_ptr<glm::mat4> &projectionMatrix, const std::shared_ptr<glm::mat4> &sceneModel);
        
        /**
        * ask the material to update the MVP Matrix and Normal Matrix in the shader.
        */
        void project();
        
        /**
         * constructor
         * initialise mesh and material. Assumes that both are not NULL pointers
         */
        Object3D(std::shared_ptr<Mesh3D> mesh, std::shared_ptr<Material> material) : Object<Vertex3D>(mesh, material) {}

        // destructor
        ~Object3D() {}
    };

}

#endif /* Object_hpp */
