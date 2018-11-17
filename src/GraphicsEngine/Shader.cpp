//
//  Shader.cpp
//  product
//
//  Created by Pierre Gabory on 16/11/2018.
//

#include "Shader.hpp"

namespace GraphicsEngine {
    
    Shader::Shader(const char* path, GLenum shaderType):
        m_glShaderIdentifier(glCreateShader(shaderType))
        {
            loadSourceCode(path, shaderType);
            compile();
        }
    
    Shader::~Shader()
    {
        glDeleteShader(m_glShaderIdentifier);
    }
    
    void Shader::loadSourceCode(const char* path, GLenum shaderType)
    {
        std::ifstream file(path);
        std::stringstream buffer;
        const char* sourceCode;
        
        if (!file) throw Exception("Failed to open Shader file.", path);
        buffer << file.rdbuf();
        sourceCode = buffer.str().c_str();
        
        glShaderSource(m_glShaderIdentifier, 1, &sourceCode, 0);
    }
    
    void Shader::compile()
    {
        glCompileShader(m_glShaderIdentifier);
        GLint status;
        glGetShaderiv(m_glShaderIdentifier, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) throw Exception("Shader Compilation failed", m_glShaderIdentifier);
    }
}
