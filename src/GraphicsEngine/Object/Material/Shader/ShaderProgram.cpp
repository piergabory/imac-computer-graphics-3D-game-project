/**
 * ShaderProgram.hpp
 */
#include "ShaderProgram.hpp"

namespace GraphicsEngine {
    
    ShaderProgram::ShaderProgram(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath) :
    // init program
    m_glProgramIdentifier(glCreateProgram())
    {
        // load shaders
        try {
            loadShader(vertexShaderSourcePath, GL_VERTEX_SHADER);
            loadShader(fragmentShaderSourcePath, GL_FRAGMENT_SHADER);
        }
        
        // check for compile success
        catch (InitialisationException error) {
            throw error;
        }
        
        // link
        glLinkProgram(m_glProgramIdentifier);
        
        // check for linking success
        GLint status;
        glGetProgramiv(m_glProgramIdentifier, GL_LINK_STATUS, &status);
        if (status != GL_TRUE) {
            throw InitialisationException("Shader program link failed", m_glProgramIdentifier);
        }
    }
    
    
    
    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_glProgramIdentifier);
    }
    
    
    
    void ShaderProgram::loadShader(const char* sourcePath, GLenum shaderType) const
    {
        // create shader
        Shader shader(sourcePath, shaderType);
        glAttachShader(m_glProgramIdentifier, shader.identifier());
    }
}
