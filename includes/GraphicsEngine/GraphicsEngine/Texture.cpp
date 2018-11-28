//
//  Texture.cpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#include "Texture.hpp"

namespace GraphicsEngine {
    
    Texture::Texture(const char* imagePath): m_image(imagePath)
    {
        glGenTextures(1, &m_glTextureIdentifier);
        glBindTexture(GL_TEXTURE_2D, m_glTextureIdentifier);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    
    Texture::~Texture() {
        glDeleteTextures(1, &m_glTextureIdentifier);
    }
    
    void Texture::linkTo(const ShaderProgram program, const char* uniformName) const {
        glActiveTexture(GL_TEXTURE0);
        GLuint uniform = glGetUniformLocation(program.identifier(), uniformName);
        glUniform1i(uniform, 0);
        glBindTexture(GL_TEXTURE_2D, m_glTextureIdentifier);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, m_image.pixels());
    }
}
