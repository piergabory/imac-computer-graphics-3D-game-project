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

    void Camera::updateCameraTransformMatrix() {
        *m_cameraTransform = glm::lookAt(m_cameraPosition + m_cameraDirection, m_cameraPosition, glm::vec3(0,1,0));
    }

    
    // constructor
    Camera::Camera(const float fieldOfView, const float aspect, const float min, const float max) :
    m_fieldOfView(fieldOfView),
    m_aspectRatio(aspect),
    m_minRenderingDistance(min),
    m_maxRenderingDistance(max),
    m_cameraTransform(new glm::mat4(1)),
    m_cameraPosition(0,0,-1),
    m_cameraDirection(0,0,-1.5){
        // defines m_projectionMatrix
        updateProjectionMatrix();
    }

    void Camera::move(const glm::vec3 &to) {
        m_cameraPosition += glm::vec3(glm::inverse(*m_cameraTransform) * glm::vec4(to,0));
        updateCameraTransformMatrix();
    }

    void Camera::pan(const glm::vec3 &axis, const float angle) {
        m_cameraDirection = glm::vec3(glm::rotate(glm::mat4(1), angle, axis) * glm::vec4(m_cameraDirection, 0));
        updateCameraTransformMatrix();
    }

    void Camera::resetPosition() {
        m_cameraPosition = glm::vec3(0,0,0);
        m_cameraDirection = glm::vec3(0,0,-1);
        updateCameraTransformMatrix();
    }


    
}