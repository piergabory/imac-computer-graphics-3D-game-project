/**
 * \file Entity.hpp
 */
#include "Entity.hpp"

namespace GameModel {
    // redefinition static member
    std::unique_ptr<GraphicsEngine::Object3D> Entity::s_entityObject;


    // static object factory
    GraphicsEngine::Object3D* Entity::makeObject(const char* meshPath, const char* texturePath, const char* vertexShaderProgram, const char* fragmentShaderProgram) {
        try {
            std::shared_ptr<GraphicsEngine::Mesh3D> mesh = std::make_shared<GraphicsEngine::ImportedMesh>(GraphicsEngine::LocalFilePath(meshPath));
            std::shared_ptr<GraphicsEngine::Texture> texture = std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath(texturePath));
            std::shared_ptr<GraphicsEngine::ShaderProgram> shaderProgram = std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(GraphicsEngine::LocalFilePath(vertexShaderProgram),GraphicsEngine::LocalFilePath(fragmentShaderProgram));
            std::shared_ptr<GraphicsEngine::Material> material = std::make_shared<GraphicsEngine::Material>(shaderProgram, texture);
            return new GraphicsEngine::Object3D(mesh, material);
        } catch(GraphicsEngine::InitialisationException error) {
            std::cerr << error.what();
            return nullptr;
        }
    }


    // static
    void Entity::loadObject() {
        s_entityObject = std::unique_ptr<GraphicsEngine::Object3D>(makeObject("assets/models/cube.obj", "assets/textures/cubemap_a.png", "shaders/perspective.vs.glsl", "shaders/flatTexture.fs.glsl"));
    }

    // constructor
    Entity::Entity() {
        if (!s_entityObject) loadObject();
        m_entityObject =  std::make_shared<GraphicsEngine::Object3D>(*s_entityObject);
    }
}
