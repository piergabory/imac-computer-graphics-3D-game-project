//
//  Material.hpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include "Texture.hpp"
#include "PerspectiveShaderProgram.hpp"

namespace GraphicsEngine {
    class Material {
    private:
        Texture* m_texture;
        PerspectiveShaderProgram* m_shader;
        
    public:
        Material(Texture *texture, PerspectiveShaderProgram *shader):
        m_texture(texture), m_shader(shader) {
            texture->linkTo(*shader);
        };
        
        ~Material() {};
        
        inline PerspectiveShaderProgram* shader() { return m_shader; }
        inline Texture* texture() { return m_texture; }
        
        void apply() const;
    };
}

#endif /* Material_hpp */
