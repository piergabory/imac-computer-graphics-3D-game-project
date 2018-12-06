/**
 * Texture.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Texture_hpp
#define Texture_hpp

#include "Frameworks.hpp"
#include "ImageData.hpp"
#include "ShaderProgram.hpp"

/**
 * TEXTURE CLASS
 *
 * Creates SDL textures and loads them in a shader sampler
 */
namespace GraphicsEngine {
    class Texture {
    private:
        // texture openGL identifier
        GLuint m_glTextureIdentifier;
        
        // image loaded from disk
        ImageData m_image;
        
    public:
        // constructor
        // load image from disk, initialize the openGL texture
        Texture(const char* imagePath);
        
        // destructor, free the openGL texture memory
        ~Texture();
        
        // links the texture instance in a shader program's texture sampler
        void linkTo(const ShaderProgram &program, const char* shaderSamplerUniform = "uMainTextureSampler") const;
        
        // getter
        inline const GLuint identifier() const { return m_glTextureIdentifier; }
        
    };
}

#endif /* Texture_hpp */
