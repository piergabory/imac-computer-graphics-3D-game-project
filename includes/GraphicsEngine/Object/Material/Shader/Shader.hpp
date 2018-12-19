/**
 * ShaderProgram.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */
#ifndef Shader_hpp
#define Shader_hpp

#include <fstream>
#include <sstream>
#include <string>

#include "Frameworks.hpp"
#include "Exceptions.hpp"

/**
 * SHADER PROGRAM CLASS
 *
 * Manages and compile vertex and fragment shaders
 */
namespace GraphicsEngine {
    
    class Shader {
    
    private:
        // shader identifier
        GLuint m_glShaderIdentifier;
        
        // read sourcecode from disk
        void loadSourceCode(const char* path, const GLenum shaderType);
        
        // compile shader
        void compile();

           std::string log() const;
        
    public:
        // constructor
        Shader(const char* path, const GLenum shaderType);
        
        // destructor
        ~Shader();
        
        // identifier getter
        inline GLuint identifier() const { return m_glShaderIdentifier; }
        inline GLuint& identifier() { return m_glShaderIdentifier; }
    };
    
}

#endif /* Shader_hpp */
