//
//  Object.cpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#include "Object.hpp"

namespace GraphicsEngine {
    void Object::applyTransformations() {
        m_normalMatrix = glm::transpose(glm::inverse(m_modelViewMatrix));
    }
    
    void Object::translate(const glm::vec3 translationVector) {
        m_modelViewMatrix = glm::translate(m_modelViewMatrix, translationVector);
        applyTransformations();
    }
    
    
    void Object::rotate(const float angle, const glm::vec3 direction) {
        m_modelViewMatrix = glm::rotate(m_modelViewMatrix, angle, direction);
        applyTransformations();
    }
    
    void Object::scale(const glm::vec3 scalingVector) {
        m_modelViewMatrix = glm::scale(m_modelViewMatrix, scalingVector);
        applyTransformations();
    }
    
    void Object::draw() const {
        glBindVertexArray(m_mesh->vertexArrayIdentifier());
        m_material->apply();
        glDrawArrays(GL_TRIANGLES, 0, m_mesh->vertexCount());
    }
}
