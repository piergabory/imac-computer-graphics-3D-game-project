/**
 * ShaderProgram.cpp
 */
#include "Shader.hpp"

namespace GraphicsEngine {
    
    Shader::Shader(const char* path, const GLenum shaderType):
    m_glShaderIdentifier(glCreateShader(shaderType)) {
        loadSourceCode(path, shaderType);
        compile();
    }
    
    Shader::~Shader() {
        glDeleteShader(m_glShaderIdentifier);
    }
    
    
    void Shader::loadSourceCode(const char* path, const GLenum shaderType) {
        std::fstream file;
        std::stringstream buffer;
        std::string tmpstring;
        const char* sourceCode;
        
        file.open(path, std::ios::in);
        
        // check if the shader file was open successfully
        if (!file.is_open())
            throw InitialisationException("Failed to open Shader file.", path);
        
        // Put file in buffer
        buffer << file.rdbuf();
        // close the buffer string
        buffer << "\0";
        
        file.close();
        
        // convert buffer into c string
        tmpstring = buffer.str();
        sourceCode = tmpstring.c_str();
        
        // load code
        glShaderSource(m_glShaderIdentifier, 1, &sourceCode, 0);
    }
    
    
    void Shader::compile() {
        glCompileShader(m_glShaderIdentifier);
        
        // check for compile status
        GLint status;
        glGetShaderiv(m_glShaderIdentifier, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE)
            throw InitialisationException("Shader Compilation failed", m_glShaderIdentifier);
    }
}
