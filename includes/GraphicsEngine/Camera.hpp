/**
 * Cameras.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Camera_hpp
#define Camera_hpp

#include <memory>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * CAMERA CLASS
 *
 * Facade to the glm projection matrix
 * provides the camera's projection matrix
 * and attributes to rotate and move the simulated camera
 */

namespace GraphicsEngine {
    
    class Camera {
        
    private:
        // camera lense properties
        float m_fieldOfView;
        float m_aspectRatio;
        
        // rendering distance
        // also defines the sampling of the zbuffer
        float m_minRenderingDistance;
        float m_maxRenderingDistance;
        
        // keeps the matrix around so we only have to
        // compute it when the camera moves
        std::shared_ptr<glm::mat4> m_projectionMatrix;

        // Spatial properties of the simulated camera
        std::shared_ptr<glm::mat4> m_cameraTransform;

        glm::vec3 m_cameraPosition;

        glm::vec3 m_cameraDirection;
        
        // updates the above matrix
        void updateProjectionMatrix();

        // recalculates the lookAt matrix
        void updateCameraTransformMatrix();

        
    public:
        // constructor
        Camera(const float fieldOfView = 120.f, const float aspect = 1, const float min = 0.1f, const float max = 100.f);
        
        // destructor
        ~Camera() {}

        // isometric transformations
        // changes the projection matrix and saves the modifications
        void move(const glm::vec3 &to);
        void pan(const glm::vec3 &orientation, const float angle);

        // reset camera to the world center.
        void resetPosition();
        
        // getter
        inline const std::shared_ptr<glm::mat4> projectionMatrix() const {
            return m_projectionMatrix;
        }

        inline const std::shared_ptr<glm::mat4> modelMatrix() const {
            return m_cameraTransform;
        }
    };
}

#endif /* Camera_hpp */
