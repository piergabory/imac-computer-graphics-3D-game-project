/**
 * \file Cameras.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Camera_hpp
#define Camera_hpp
#pragma once

#include <memory>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Animation.hpp"

namespace GraphicsEngine {

    enum class CameraControl {
        TURNTABLE, FLY
    };

    /**
     * CAMERA CLASS
     *
     * \brief Facade to the glm projection matrix
     * provides the camera's projection matrix
     * and attributes to rotate and move the simulated camera
     */
    class Camera : public Animatable {
        
    private:
        // camera lense properties
        float m_fieldOfView;
        float m_aspectRatio;
        
        // rendering distance
        // also defines the sampling of the zbuffer
        float m_minRenderingDistance;
        float m_maxRenderingDistance;

        // define the rotation and translation behavior
        CameraControl m_controlMode = CameraControl::TURNTABLE;
        
        // keeps the matrix around so we only have to
        // compute it when the camera moves
        std::shared_ptr<glm::mat4> m_projectionMatrix;

        // Spatial properties of the simulated camera
        std::shared_ptr<glm::mat4> m_cameraTransform;

        // point used to place the camera with glm::lookAt
        glm::vec3 m_cameraPosition;

        // vector used to point the camera with glm::lookAt
        glm::vec3 m_cameraDirection;
        
        // updates the above matrix
        void updateProjectionMatrix();

        // recalculates the lookAt matrix
        void updateCameraTransformMatrix();

        
    public:
        // constructor
        Camera(const float fieldOfView = 60.f, const float aspect = 800.f/600.f, const float min = 0.1f, const float max = 100.f);
        
        // destructor
        ~Camera() {}

        // isometric transformations
        // changes the projection matrix and saves the modification
        inline const glm::vec3 position() const override;
        void translate(const glm::vec3& direction) override;
        void place(const glm::vec3& direction) override;
        void rotate(const float angle, const glm::vec3 &direction) override;

        // reset camera to the world center.
        void resetPosition();

        // change camera control mode
        void switchMode(CameraControl mode);
        
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
