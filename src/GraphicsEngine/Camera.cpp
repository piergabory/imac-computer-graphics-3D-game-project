/**
 * Cameras.hpp
 */

#include "Camera.hpp"

namespace GraphicsEngine {
    
    void Camera::updateProjectionMatrix() {
        // compute camera projection
        glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(m_fieldOfView), m_aspectRatio, m_minRenderingDistance, m_maxRenderingDistance);
        
        m_projectionMatrix = std::make_shared<glm::mat4>(perspectiveMatrix);
    }
    
    
    // constructor
    Camera::Camera(const float fieldOfView, const float aspect, const float min, const float max) :
    m_fieldOfView(fieldOfView), m_aspectRatio(aspect), m_minRenderingDistance(min), m_maxRenderingDistance(max), m_cameraTransform(new glm::mat4(1)) {
        // defines m_projectionMatrix
        updateProjectionMatrix();
    }

    void Camera::translate(const glm::vec3 &to) {
        *m_cameraTransform = glm::translate(*m_cameraTransform, to);
    }

    void Camera::rotate(const glm::vec3 &orientation, const float angle) {
        *m_cameraTransform = *m_cameraTransform * glm::rotate(glm::mat4(1), angle, orientation);
    }
    
}
