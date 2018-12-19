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
            LocalFilePath vertexShaderSourcePath,
            LocalFilePath fragmentShaderSourcePath,
            const char* uniformMVPName = "uMVPMatrix",
            const char* uniformMVName = "uMVMatrix",
            const char* uniformNormName = "uNormalMatrix");

        PerspectiveShaderProgram(const PerspectiveShaderProgram &copy) = default;
        PerspectiveShaderProgram& operator=(const PerspectiveShaderProgram &source) = default;

        
        // destructor
        ~PerspectiveShaderProgram() {};

        // computes the Model View Projection Matrix and applys it to the shader uniforms;
        void setUniformMatrices(const glm::mat4 &objectModel) const;

        // link the desired camera matrices (projection and world->view)
        void setViewMatrices(const std::shared_ptr<glm::mat4> &projection,  const std::shared_ptr<glm::mat4> &sceneModel);
    };
    
}

#endif /* PerspectiveShaderProgram_hpp */
