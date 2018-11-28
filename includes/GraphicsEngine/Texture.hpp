//
//  Texture.hpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "Frameworks.hpp"
#include "ImageData.hpp"
#include "ShaderProgram.hpp"


namespace GraphicsEngine {
    class Texture {
    private:
        GLuint m_glTextureIdentifier;
        ImageData m_image;
        
    public:
        Texture(const char* imagePath);
        ~Texture();
        
        void linkTo(const ShaderProgram &program, const char* uniformName = "uMainTextureSampler") const;
        
        inline GLuint identifier() const { return m_glTextureIdentifier; }
        
    };
}

#endif /* Texture_hpp */
