/**
 * Material.cpp
 */

#include "Material.hpp"

namespace GraphicsEngine {
    
    Material::Material(std::shared_ptr<ShaderProgram> shader, std::shared_ptr<Texture>texture) :
    m_texture(texture), m_shader(shader) {
        if (m_texture) {
            // sends the texture(s) to the shader texture sampler
            texture->linkTo(*shader);
        }
    };

    Material::Material(ShaderProgram* shader, Texture* texture) :
    m_texture(std::shared_ptr<Texture>(texture)), m_shader(std::shared_ptr<ShaderProgram>(shader)) {
        if (m_texture) {
            // sends the texture(s) to the shader texture sampler
            texture->linkTo(*shader);
        }
    }
    
    
    void Material::apply() const {
        // activate the shader program
        m_shader->use();
        
        // select the texture
        if (m_texture) {
            glBindTexture(GL_TEXTURE_2D, m_texture->identifier());
        }
    }
    
}
