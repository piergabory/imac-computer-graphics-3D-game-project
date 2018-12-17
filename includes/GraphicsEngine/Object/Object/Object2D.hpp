//
//  Object2D.hpp
//  xcode target
//
//  Created by Pierre Gabory on 17/12/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef Object2D_hpp
#define Object2D_hpp


#include "Object.hpp"

namespace GraphicsEngine {
    class Object2D : public Object<Vertex2D> {
    private:
        static ShaderProgram m_2dShader;
        static std::shared_ptr<Material> createMaterial(const char* textureImagePath);
        static std::shared_ptr<Material> createMaterial(std::shared_ptr<Texture> &texture);
        static std::shared_ptr<Mesh2D> createBoundingBox(glm::vec2 &position, glm::vec2 &size);

        static void initialize2DShaderProgram(LocalFilePath &vertexShaderPath, LocalFilePath  &framgmentShaderPath);

    public:
        Object2D(glm::vec2 &position, glm::vec2 &size, const char* image) : Object<Vertex2D>(createBoundingBox(position, size), createMaterial(image)) {}

        Object2D(glm::vec2 &position, glm::vec2 &size, std::shared_ptr<Texture> &texture) : Object<Vertex2D>(createBoundingBox(position, size), createMaterial(texture)) {}
    };
}

#endif /* Object2D_hpp */
