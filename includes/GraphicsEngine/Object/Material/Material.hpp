/**
 * Material.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */
#ifndef Material_hpp
#define Material_hpp

#include "Texture.hpp"
#include "PerspectiveShaderProgram.hpp"

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
        Texture* m_texture;
        
        // shader pointer
        // perspective shader handles projection
        PerspectiveShaderProgram* m_shader;
        
        
    public:
        // constructor
        Material(PerspectiveShaderProgram *shader, Texture *texture = nullptr);
        
        // destructor
        ~Material() {};
        
        // getters
        inline PerspectiveShaderProgram* shader() { return m_shader; }
        inline const PerspectiveShaderProgram* shader() const { return m_shader; }

        inline Texture* texture() { return m_texture; }
        inline const Texture* texture() const { return m_texture; }
        
        // activate the shader program and select the textures
        void apply() const;
    };
    
}

#endif /* Material_hpp */
