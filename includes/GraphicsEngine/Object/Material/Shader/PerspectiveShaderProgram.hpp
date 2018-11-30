/**
 * PerspectiveShaderProgram.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef PerspectiveShaderProgram_hpp
#define PerspectiveShaderProgram_hpp

#include "Frameworks.hpp"
#include "ShaderProgram.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * PERSPECTIVE SHADER PROGRAM CLASS
 *
 * Adds matrix uniforms management to the ShaderProgram class.
 */
namespace GraphicsEngine {
    
    class PerspectiveShaderProgram : public ShaderProgram {
        
    private:
        // perspective matrices
        GLuint m_uniformModelViewMatrix;
        GLuint m_uniformNormalMatrix;
        GLuint m_uniformModelViewProjectionMatrix;
        
        void findUniforms();
        
    public:
        // constructor
        PerspectiveShaderProgram(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
        
        // destructor
        ~PerspectiveShaderProgram() {};
        
        // matrices setter
        // takes the object's modelview and the camera's projection, computes the rest
        void setUniformMatrices(const glm::mat4 &modelView, const glm::mat4 &projection);
    };
    
}

#endif /* PerspectiveShaderProgram_hpp */
