/**
 * \file Game.hpp
 */
#include "Game.hpp"

namespace GameModel {

    void Game::update(float chunkProgress) {
        m_enemyOffset.push(m_terrain.progress(chunkProgress));
        m_terrain.entityAt(m_player.position())->test(m_player);

        if (m_enemyOffset.size() > m_player.life()) do {
            m_enemy->globalTranslate(m_enemyOffset.back() - m_enemyOffset.front());
            m_enemyOffset.pop();
        } while(m_enemyOffset.size() < m_player.life());

    }

    void Game::nextChunk() {
        CardinalDirections previousOrientation = m_terrain.facing();
        m_terrain.nextChunk();
        
        if (previousOrientation != m_terrain.facing())
            m_player.resetPosition();
    }

    /// \brief Redirects controller inputs on player movements, attacks, bonuses etc...
    void Game::callInput(Controls control) {
        switch(control) {
            case Controls::LEFT:
                m_player.move(Direction::LEFT);
                break;

            case Controls::RIGHT:
                m_player.move(Direction::RIGHT);
                break;

            case Controls::UP:
                m_player.jump();
                break;

            case Controls::DOWN:
                m_player.crouch();
                break;
        }
    }

    // constructor
    Game::Game() :
        m_player(loadPlayerObject()),
        m_enemy(loadEnemyObject())
    {}

    // destructor
    Game::~Game() {}


    // static method generating player character models
    std::shared_ptr<GraphicsEngine::Object3D> Game::loadPlayerObject() {

        // define resources paths
        const GraphicsEngine::LocalFilePath
        PLAYER_MESH("assets/models/monkey1.obj"),
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


    // static method generating player character models
    std::shared_ptr<GraphicsEngine::Object3D> Game::loadEnemyObject() {

        // define resources paths
        const GraphicsEngine::LocalFilePath
        PLAYER_MESH("assets/models/monkey1.obj"),
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

}
