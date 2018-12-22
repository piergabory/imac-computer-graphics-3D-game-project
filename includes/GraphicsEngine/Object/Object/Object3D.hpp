/**
 * \file Object3D.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Object_hpp
#define Object_hpp

#include "Object.hpp"
#include "PerspectiveShaderProgram.hpp"

namespace GraphicsEngine {


    /**
     * OBJECT 3D CLASS
     *
     * \brief object subclass for 3 dimentional instances.
     * \version 0.2
     *
     * is hable to handle 3D Projection and perspective shaders
     * Adds transformations methods to move around objects in the scene
     */
    class Object3D : public Object<Vertex3D> {

    private:
        /// \brief Model-View Matrix, represents the position/rotation/scale of the object in the scene.
        glm::mat4 m_modelViewMatrix;
        
    public:

        /// \brief places move the object to coordinates
        void place(const glm::vec3 &newPosition);

        /// \brief apply a 3D translation on the object
        void translate(const glm::vec3 &translationVector);

        /// \brief apply a 3D rotation on the object
        void rotate(const float angle, const glm::vec3 &direction);

        /// \brief apply a 3D scale on the object
        void scale(const glm::vec3 &scalingVector);


        /// \brief link the scene camera's matrices to the perspective shader.
        void setProjection(const std::shared_ptr<glm::mat4> &projectionMatrix, const std::shared_ptr<glm::mat4> &sceneModel);

        /// \brief ask the material to update the MVP Matrix and Normal Matrix in the shader.
        void project();


        /// \brief position getter
        inline const glm::vec3 position() const {
            return glm::vec3(m_modelViewMatrix * glm::vec4(0,0,0,1));
        }

        // constructor
        /// \brief initialise mesh and material. Assumes the material shader is of perspective kind.
        Object3D(std::shared_ptr<Mesh3D> mesh, std::shared_ptr<Material> material);

        // destructor
        ~Object3D() {}
    };

}

#endif /* Object_hpp */
