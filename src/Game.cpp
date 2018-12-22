#include "Game.hpp"

Game::Game() : m_pPlayer(loadPlayerObject()) {}

Game::~Game() {}

std::shared_ptr<GraphicsEngine::Object3D> Game::loadPlayerObject() {
    const GraphicsEngine::LocalFilePath
    PLAYER_MESH("assets/monkey1.obj"),
    PLAYER_TEXTURE("assets/textures/test.png"),
    VERTEX_SHADER("shaders/perspective.vs.glsl"),
    FRAGMENT_SHADER("shaders/flatTexture.fs.glsl");

    return std::make_shared<GraphicsEngine::Object3D>(
std::make_shared<GraphicsEngine::ImportedMesh>(PLAYER_MESH),
std::make_shared<GraphicsEngine::Material>(
std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(VERTEX_SHADER, FRAGMENT_SHADER),
std::make_shared<GraphicsEngine::Texture>(PLAYER_TEXTURE)
)
                                                  );
}
