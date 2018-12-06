/**
 * Cameras.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Camera_hpp
#define Camera_hpp

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
        glm::mat4 m_projectionMatrix;

        // Spatial properties of the simulated camera
        glm::mat4 m_cameraTransform;
        
        // updates the above matrix
        void updateProjectionMatrix();
        
    public:
        // constructor
        Camera(const float fieldOfView = 90,
               const float aspect = 4/3,
               const float min = 0.1f,
               const float max = 100.f);
        
        // destructor
        ~Camera() {}

        // isometric transformations
        // changes the projection matrix and saves the modifications
        void translate(const glm::vec3 &to);
        void rotate(const glm::vec3 &orientation, const float angle);
        
        // getter
        inline const glm::mat4 projectionMatrix() const { return m_projectionMatrix; }
    };
}

#endif /* Camera_hpp */
