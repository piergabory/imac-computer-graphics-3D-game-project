//
//  Shader.hpp
//  product
//
//  Created by Pierre Gabory on 16/11/2018.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <fstream>
#include <sstream>
#include <string>

#include "Frameworks.hpp"
#include "Exceptions.hpp"

namespace GraphicsEngine {
    
    class Shader {
    
    private:
        GLuint m_glShaderIdentifier;
        
        void loadSourceCode(const char* path, const GLenum shaderType);
        void compile();
        
    public:
        Shader(const char* path, const GLenum shaderType);
        ~Shader();
        
        inline GLuint identifier() const { return m_glShaderIdentifier; }
        inline GLuint& identifier() { return m_glShaderIdentifier; }
    };
    
}

#endif /* Shader_hpp */
