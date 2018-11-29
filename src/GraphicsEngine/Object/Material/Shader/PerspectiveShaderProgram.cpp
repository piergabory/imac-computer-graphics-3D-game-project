/**
 * PerspectiveShaderProgram.hpp
 */
#include "PerspectiveShaderProgram.hpp"

namespace GraphicsEngine {
    
    PerspectiveShaderProgram::PerspectiveShaderProgram(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath) :
    ShaderProgram(vertexShaderSourcePath, fragmentShaderSourcePath) {
        findUniforms();
    }
    
    void PerspectiveShaderProgram::findUniforms() {
        m_uniformModelViewMatrix = glGetUniformLocation(m_glProgramIdentifier, "uMVPMatrix");
        m_uniformNormalMatrix = glGetUniformLocation(m_glProgramIdentifier, "uMVMatrix");
        m_uniformModelViewProjectionMatrix = glGetUniformLocation(m_glProgramIdentifier, "uNormalMatrix");
    }
    
    void PerspectiveShaderProgram::setUniformMatrices(const glm::mat4 &modelView, const glm::mat4 &projection) {
        // modelview = modelview
        glUniformMatrix4fv(m_uniformModelViewMatrix, 1, false, glm::value_ptr(modelView));
        
        // Normal = transversed( inverted( modelview ))
        // the 'true' parameter asks the method to do the transvertion of the input matrix.
        glUniformMatrix4fv(m_uniformNormalMatrix, 1, true, glm::value_ptr(glm::inverse(modelView)));
        
        // modelviewProjection = modelview * projection
        glUniformMatrix4fv(m_uniformModelViewProjectionMatrix, 1, false, glm::value_ptr(modelView * projection));
    }
}
