/**
 * Material.cpp
 */

#include "Material.hpp"

namespace GraphicsEngine {
    
    Material::Material(Texture *texture, PerspectiveShaderProgram *shader) :
    m_texture(texture), m_shader(shader) {
        // sends the texture(s) to the shader texture sampler
        texture->linkTo(*shader);
    };
    
    
    void Material::apply() const {
        // activate the shader program
        m_shader->use();
        
        // select the texture
        glBindTexture(GL_TEXTURE_2D, m_texture->identifier());
    }
    
}
