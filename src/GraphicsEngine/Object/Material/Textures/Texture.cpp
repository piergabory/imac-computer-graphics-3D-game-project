/**
 * Texture.cpp
 */

#include "Texture.hpp"

namespace GraphicsEngine {
    Texture::Texture(LocalFilePath imagePath): m_image(imagePath.c_str()) {
        generateTexture();
    }

    // constructor
    Texture::Texture(const char* imagePath): m_image(imagePath) {
        generateTexture();
    }

    void Texture::generateTexture() {
        // generate texture
        glGenTextures(1, &m_glTextureIdentifier);

        // select texture
        glBindTexture(GL_TEXTURE_2D, m_glTextureIdentifier);

        // set scaling parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    
    Texture::~Texture() {
        // dealloc opengl texture
        glDeleteTextures(1, &m_glTextureIdentifier);
    }
    
    void Texture::linkTo(const ShaderProgram &program, const char* shaderSamplerUniform) const {
        // use the first channel
        glActiveTexture(GL_TEXTURE0);
        
        // find uniform in the shaderprogram
        GLuint uniform = glGetUniformLocation(program.identifier(), shaderSamplerUniform);
        glUniform1i(uniform, 0);
        
        // bind texture to the uniform sampler
        glBindTexture(GL_TEXTURE_2D, m_glTextureIdentifier);

        #if __APPLE__
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, m_image.pixels());
        #else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.pixels());
        #endif
    }
}
