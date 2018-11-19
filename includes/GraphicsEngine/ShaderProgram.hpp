//
//  ShaderProgram.hpp
//  product
//
//  Created by Pierre Gabory on 16/11/2018.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <string>

#include "Frameworks.hpp"
#include "Exceptions.hpp"
#include "Shader.hpp"

namespace GraphicsEngine
{
    class ShaderProgram
    {
        
    private:
        GLuint m_glProgramIdentifier;
        
        void loadShader(const char* sourcePath, GLenum shaderType) const;
        
        std::string log() const;
        
    public:
        inline const GLuint identifier() const {
            return m_glProgramIdentifier;
        }
        
        inline void use() const {
            glUseProgram(m_glProgramIdentifier);
        }
        
        ShaderProgram(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
        
        ~ShaderProgram();
    };
}

#endif /* ShaderProgram_hpp */
