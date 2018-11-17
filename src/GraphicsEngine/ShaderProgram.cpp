//
//  ShaderProgram.cpp
//  product
//
//  Created by Pierre Gabory on 16/11/2018.
//

#include "ShaderProgram.hpp"

namespace GraphicsEngine
{
    
    ShaderProgram::ShaderProgram(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
    : m_glProgramIdentifier(glCreateProgram())
    {
        loadShader(vertexShaderSourcePath, GL_VERTEX_SHADER);
        loadShader(fragmentShaderSourcePath, GL_FRAGMENT_SHADER);
        
        
        glLinkProgram(m_glProgramIdentifier);
        GLint status;
        glGetProgramiv(m_glProgramIdentifier, GL_LINK_STATUS, &status);
        if (status != GL_TRUE) throw Exception("Shader program link failed", m_glProgramIdentifier);
    }
    
    
    
    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_glProgramIdentifier);
    }
    
    
    
    void ShaderProgram::use() const
    {
        glUseProgram(m_glProgramIdentifier);
    }
    
    
    
    void ShaderProgram::loadShader(const char* sourcePath, GLenum shaderType) const
    {
        Shader shader(sourcePath, shaderType);
        glAttachShader(m_glProgramIdentifier, shader.identifier());
    }
    
    
    
    const GLuint ShaderProgram::identifier() const
    {
        return m_glProgramIdentifier;
    }
}
