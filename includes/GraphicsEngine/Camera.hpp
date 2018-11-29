//
//  Camera.hpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//

#ifndef Camera_hpp
#define Camera_hpp

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GraphicsEngine {
    class Camera {
    private:
        glm::vec3 m_position;
        glm::vec3 m_orientation;
        float m_angle;
        
        float m_fieldOfView;
        float m_aspectRatio;
        
        float m_minRenderingDistance;
        float m_maxRenderingDistance;
        
        glm::mat4 m_projectionMatrix;
        
        void updateProjectionMatrix();
        
    public:
        Camera(const float fieldOfView = 90,
               const float aspect = 4/3,
               const float min = 0.1f,
               const float max = 100.f);
        
        ~Camera() {}
        
        inline const glm::mat4 projectionMatrix() const { return m_projectionMatrix; }
    };
}

#endif /* Camera_hpp */
