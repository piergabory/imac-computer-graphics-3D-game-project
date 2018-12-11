/**
 * Object.cpp
 */
#include "Object.hpp"


namespace GraphicsEngine {

    void Object::setProjection(const std::shared_ptr<glm::mat4> &projectionMatrix, const std::shared_ptr<glm::mat4> &sceneModel) {
        m_material->shader()->setViewMatrices(projectionMatrix, sceneModel);
    }
    
    void Object::translate(const glm::vec3 &translationVector) {
        m_modelViewMatrix = glm::translate(m_modelViewMatrix, translationVector);
    }
    
    
    void Object::rotate(const float angle, const glm::vec3 &direction) {
        m_modelViewMatrix = glm::rotate(m_modelViewMatrix, angle, direction);
    }
    
    
    void Object::scale(const glm::vec3 &scalingVector) {
        m_modelViewMatrix = glm::scale(m_modelViewMatrix, scalingVector);
    }
    
    
    void Object::project() {
        m_material->shader()->setUniformMatrices(m_modelViewMatrix);
    }
    
    
    void Object::draw() const {
        glBindVertexArray(m_mesh->vertexArrayIdentifier());
        m_material->apply();
        
        glDrawArrays(m_mesh->mode(), 0, m_mesh->vertexCount());
    }
    
}
