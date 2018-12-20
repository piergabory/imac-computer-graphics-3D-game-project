/**
 * \file Object3D.cpp
 */
#include "Object3D.hpp"


namespace GraphicsEngine {

    void Object3D::setProjection(const std::shared_ptr<glm::mat4> &projectionMatrix, const std::shared_ptr<glm::mat4> &sceneModel) {
        static_cast<PerspectiveShaderProgram *>(m_material->shader())->setViewMatrices(projectionMatrix, sceneModel);
    }


    void Object3D::translate(const glm::vec3 &translationVector) {
        m_modelViewMatrix = glm::translate(m_modelViewMatrix, translationVector);
    }
    
    
    void Object3D::rotate(const float angle, const glm::vec3 &direction) {
        m_modelViewMatrix = glm::rotate(m_modelViewMatrix, angle, direction);
    }
    
    
    void Object3D::scale(const glm::vec3 &scalingVector) {
        m_modelViewMatrix = glm::scale(m_modelViewMatrix, scalingVector);
    }
    
    
    void Object3D::project() {
        static_cast<PerspectiveShaderProgram *>(m_material->shader())->setUniformMatrices(m_modelViewMatrix);
        
    }


    Object3D::Object3D(std::shared_ptr<Mesh3D> mesh, std::shared_ptr<Material> material) : Object<Vertex3D>(mesh, material) {
        
    }

}
