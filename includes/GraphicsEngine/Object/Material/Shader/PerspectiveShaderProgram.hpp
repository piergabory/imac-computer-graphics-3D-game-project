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

#include <memory>

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
        std::shared_ptr<glm::mat4> m_projectionMatrix;
        std::shared_ptr<glm::mat4> m_sceneModelViewMatrix;

        // perspective matrices
        GLuint m_uniformModelViewMatrix;
        GLuint m_uniformNormalMatrix;
        GLuint m_uniformModelViewProjectionMatrix;
        
        void findUniforms();
        
    public:
        // constructor
        PerspectiveShaderProgram(
            const char* vertexShaderSourcePath,
            const char* fragmentShaderSourcePath,
            const char* uniformMVPName = "uMVPMatrix",
            const char* uniformMVName = "uMVMatrix",
            const char* uniformNormName = "uNormalMatrix");
        
        // destructor
        ~PerspectiveShaderProgram() {};

        // TODO: documentation
        void setUniformMatrices(const glm::mat4 &objectModel) const;

        void setViewMatrices(const std::shared_ptr<glm::mat4> &projection,  const std::shared_ptr<glm::mat4> &sceneModel);
    };
    
}

#endif /* PerspectiveShaderProgram_hpp */
