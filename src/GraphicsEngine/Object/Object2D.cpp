//
//  Object2D.cpp
//  xcode target
//
//  Created by Pierre Gabory on 17/12/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#include "Object2D.hpp"

namespace GraphicsEngine {

    std::shared_ptr<ShaderProgram> Object2D::m_2dShader;

    std::shared_ptr<Mesh2D> Object2D::createBoundingBox(glm::vec2 &position, glm::vec2 &size) {
        std::vector<Vertex2D> vertices;
        vertices.push_back(Vertex2D(position, glm::vec2(0,0)));
        vertices.push_back(Vertex2D(position + glm::vec2(size.x, 0), glm::vec2(1,0)));
        vertices.push_back(Vertex2D(position + size, glm::vec2(1,1)));
        vertices.push_back(Vertex2D(position + glm::vec2(0, size.y), glm::vec2(0,1)));
        return std::make_shared<Mesh2D>(vertices, GL_TRIANGLE_FAN);
    }

    std::shared_ptr<Material> Object2D::createMaterial(LocalFilePath textureImagePath) {
        assert(m_2dShader->identifier() != 0);
        std::shared_ptr<Texture> texture = std::make_shared<Texture>(textureImagePath);
        return std::make_shared<Material>(m_2dShader, texture);
    }

    std::shared_ptr<Material> Object2D::createMaterial(std::shared_ptr<Texture> &texture) {
        assert(m_2dShader->identifier() != 0);
        return std::make_shared<Material>(m_2dShader, texture);
    }
    
    void Object2D::initialize2DShaderProgram(LocalFilePath vertexShaderPath, LocalFilePath fragementShaderPath) {
        m_2dShader = std::make_shared<ShaderProgram>(vertexShaderPath, fragementShaderPath);
    }
}
