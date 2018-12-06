/**
 * PerspectiveShaderProgram.hpp
 */
#include "PerspectiveShaderProgram.hpp"

namespace GraphicsEngine {
    
    PerspectiveShaderProgram::PerspectiveShaderProgram(
       const char* vertexShaderSourcePath, 
       const char* fragmentShaderSourcePath,
       const char* uniformMVPName, 
       const char* uniformMVName, 
       const char* uniformNormName):

    // superclass constructor
        ShaderProgram(vertexShaderSourcePath, fragmentShaderSourcePath),

    // members init
        m_uniformModelViewMatrix(glGetUniformLocation(m_glProgramIdentifier, uniformMVPName)),
        m_uniformNormalMatrix(glGetUniformLocation(m_glProgramIdentifier, uniformMVName)),
        m_uniformModelViewProjectionMatrix(glGetUniformLocation(m_glProgramIdentifier, uniformNormName))

    // nothing
    {}

    
    void PerspectiveShaderProgram::setUniformMatrices(const glm::mat4 &modelView, const glm::mat4 &projection) {
        // modelview = modelview
        glUniformMatrix4fv(m_uniformModelViewMatrix, 1, false, glm::value_ptr(modelView));
        
        // Normal = transversed( inverted( modelview ))
        // the 'true' parameter asks the method to do the transvertion of the input matrix.
        glUniformMatrix4fv(m_uniformNormalMatrix, 1, true, glm::value_ptr(glm::inverse(modelView)));
        
        // modelviewProjection = modelview * projection
        glUniformMatrix4fv(m_uniformModelViewProjectionMatrix, 1, false, glm::value_ptr(projection * modelView));
    }
}
