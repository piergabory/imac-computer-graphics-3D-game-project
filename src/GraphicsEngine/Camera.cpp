/**
 * Cameras.hpp
 */

#include "Camera.hpp"

namespace GraphicsEngine {
    
    void Camera::updateProjectionMatrix() {
        // compute camera projection
        m_projectionMatrix = glm::perspective(glm::radians(m_fieldOfView),
                                              m_aspectRatio,
                                              m_minRenderingDistance,
                                              m_maxRenderingDistance);
        
        // move the camera
        m_projectionMatrix = glm::translate(glm::mat4(1), m_position) * m_projectionMatrix;
        m_projectionMatrix = glm::rotate(glm::mat4(1), m_angle, m_orientation) * m_projectionMatrix;
    }
    
    
    // constructor
    Camera::Camera(const float fieldOfView, const float aspect, const float min, const float max) :
    m_angle(0), m_fieldOfView(fieldOfView), m_aspectRatio(aspect), m_minRenderingDistance(min), m_maxRenderingDistance(max) {
        // defines m_projectionMatrix
        updateProjectionMatrix();
    }
    
}
