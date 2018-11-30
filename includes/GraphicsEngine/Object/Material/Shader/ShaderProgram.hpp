/**
 * ShaderProgram.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */
#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <string>

#include "Frameworks.hpp"
#include "Exceptions.hpp"
#include "Shader.hpp"

/**
 * SHADER PROGRAM CLASS
 *
 * Manages and compile vertex and fragment shaders
 */
namespace GraphicsEngine {
    
    class ShaderProgram {
        
    private:
        // Load a shader from file
        void loadShader(const char* sourcePath, GLenum shaderType) const;
        
        // creates a string of the compile log.
        std::string log() const;
        
    protected:
        // program GL identifier
        GLuint m_glProgramIdentifier;
        
    public:
        // const identifier getter
        inline const GLuint identifier() const {
            return m_glProgramIdentifier;
        }
    
        // identifier getter
        inline GLuint& identifier() {
            return m_glProgramIdentifier;
        }
        
        // activate the shader
        inline void use() const {
            glUseProgram(m_glProgramIdentifier);
        }
        
        // constructor, takes in the paths of the vertex shader and fragment shader
        ShaderProgram(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
        
        // destructor
        ~ShaderProgram();
    };
    
}

#endif /* ShaderProgram_hpp */
