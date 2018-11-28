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
#include "ShaderProgram.hpp"

namespace GraphicsEngine {
    class Material {
    private:
        Texture* m_texture;
        ShaderProgram* m_shader;
        
    public:
        Material(Texture *texture, ShaderProgram *shader):
        m_texture(texture), m_shader(shader) {
            texture->linkTo(*shader);
        };
        
        ~Material() {};
        
        void apply() const;
    };
}

#endif /* Material_hpp */
