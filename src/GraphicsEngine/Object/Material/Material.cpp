//
//  Material.cpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#include "Material.hpp"

namespace GraphicsEngine {
    void Material::apply() const {
        m_shader->use();
        glBindTexture(GL_TEXTURE_2D, m_texture->identifier());
    }
}
