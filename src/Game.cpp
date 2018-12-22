/**
 * \file Game.hpp
 */
#include "Game.hpp"

// static method generating player character models
std::shared_ptr<GraphicsEngine::Object3D> Game::loadPlayerObject() {

    // define resources paths
    const GraphicsEngine::LocalFilePath
    PLAYER_MESH("assets/monkey1.obj"),
    PLAYER_TEXTURE("assets/textures/test.png"),
    VERTEX_SHADER("shaders/perspective.vs.glsl"),
    FRAGMENT_SHADER("shaders/flatTexture.fs.glsl");

    // creates player character model
    std::shared_ptr<GraphicsEngine::ShaderProgram> playerShader = std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(VERTEX_SHADER, FRAGMENT_SHADER);
    std::shared_ptr<GraphicsEngine::Texture> playerTexture = std::make_shared<GraphicsEngine::Texture>(PLAYER_TEXTURE);
    std::shared_ptr<GraphicsEngine::Material> playerMaterial = std::make_shared<GraphicsEngine::Material>(playerShader, playerTexture);
    std::shared_ptr<GraphicsEngine::Mesh3D> playerMesh = std::make_shared<GraphicsEngine::ImportedMesh>(PLAYER_MESH);
    return std::make_shared<GraphicsEngine::Object3D>(playerMesh, playerMaterial);
}


/// \brief Redirects controller inputs on player movements, attacks, bonuses etc...
void Game::callInput(Controls control) {
    switch(control) {
        case Controls::LEFT:
            m_pPlayer.move(Direction::LEFT);
            break;

        case Controls::RIGHT:
            m_pPlayer.move(Direction::RIGHT);
            break;

        case Controls::UP:
            m_pPlayer.jump();
            break;

        case Controls::DOWN:
            m_pPlayer.crouch();
            break;
    }
}


// constructor
Game::Game() : m_pPlayer(loadPlayerObject()) {}

// destructor
Game::~Game() {}
