////
////  PerspectiveShaderProgram.cpp
////  xcode target
////
////  Created by Pierre Gabory on 28/11/2018.
////  Copyright © 2018 Pierre Gabory. All rights reserved.
////
#include "PerspectiveShaderProgram.hpp"

namespace GraphicsEngine {
    PerspectiveShaderProgram::PerspectiveShaderProgram(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath) : ShaderProgram(vertexShaderSourcePath, fragmentShaderSourcePath)
    {
        findUniforms();
    }
    
    void PerspectiveShaderProgram::findUniforms() {
        m_uniformModelViewMatrix = glGetUniformLocation(m_glProgramIdentifier, "uMVPMatrix");
        m_uniformNormalMatrix = glGetUniformLocation(m_glProgramIdentifier, "uMVMatrix");
        m_uniformModelViewProjectionMatrix = glGetUniformLocation(m_glProgramIdentifier, "uNormalMatrix");
        m_uniformTextureSampler = glGetUniformLocation(m_glProgramIdentifier, "uTexture");
    }
    
    void PerspectiveShaderProgram::setUniformMatrices(const glm::mat4 &modelView, const glm::mat4 &projection) {
        glUniformMatrix4fv(m_uniformModelViewMatrix, 1, false, glm::value_ptr(modelView));
        glUniformMatrix4fv(m_uniformNormalMatrix, 1, true, glm::value_ptr(glm::inverse(modelView)));
        glUniformMatrix4fv(m_uniformModelViewProjectionMatrix, 1, false, glm::value_ptr(modelView * projection));
    }
}
