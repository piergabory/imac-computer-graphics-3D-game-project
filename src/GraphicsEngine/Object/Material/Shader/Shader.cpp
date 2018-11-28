//
//  Shader.cpp
//  product
//
//  Created by Pierre Gabory on 16/11/2018.
//

#include "Shader.hpp"

namespace GraphicsEngine {
    
    Shader::Shader(const char* path, const GLenum shaderType):
        m_glShaderIdentifier(glCreateShader(shaderType))
        {
            loadSourceCode(path, shaderType);
            compile();
        }
    
    Shader::~Shader()
    {
        glDeleteShader(m_glShaderIdentifier);
    }
    
    void Shader::loadSourceCode(const char* path, const GLenum shaderType)
    {
        std::ifstream file;
        file.open(path, std::ios::in);
        std::stringstream buffer;
        std::string secondBuffer;
        const char* sourceCode;
        
        if (!file.is_open())
            throw InitialisationException("Failed to open Shader file.", path);
        
        buffer << file.rdbuf();
        buffer << "\0";
        secondBuffer = buffer.str();
        sourceCode = secondBuffer.c_str();
        file.close();
        
        glShaderSource(m_glShaderIdentifier, 1, &sourceCode, 0);
    }
    
    void Shader::compile()
    {
        glCompileShader(m_glShaderIdentifier);
        GLint status;
        glGetShaderiv(m_glShaderIdentifier, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE)
            throw InitialisationException("Shader Compilation failed", m_glShaderIdentifier);
    }
}
