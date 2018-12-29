/**
 * Material.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */
#ifndef Material_hpp
#define Material_hpp
#pragma once

#include <memory>

#include "Texture.hpp"
#include "ShaderProgram.hpp"

/**
 * MATERIAL CLASS
 *
 * Controls the appearance of 3D objects
 * Manages texture and shaders.
 */
namespace GraphicsEngine {
    
    class Material {
        
    private:
        // texture pointer
        std::shared_ptr<Texture> m_texture;
        
        // shader pointer
        // perspective shader handles projection
        std::shared_ptr<ShaderProgram> m_shader;
        
        
    public:
        // constructor
        Material(std::shared_ptr<ShaderProgram> shader, std::shared_ptr<Texture> texture = nullptr);
        // deprecated constructor
        Material(ShaderProgram* shader, Texture* texture = nullptr);
        
        // destructor
        ~Material() {};
        
        // getters
        inline ShaderProgram* shader() { return m_shader.get(); }
        inline const ShaderProgram* shader() const { return m_shader.get(); }

        inline Texture* texture() { return m_texture.get(); }
        inline const Texture* texture() const { return m_texture.get(); }
        
        // activate the shader program and select the textures
        void apply() const;
    };
    
}

#endif /* Material_hpp */
