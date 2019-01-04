/**
 * \file Game.hpp
 */
#include "Game.hpp"

namespace GameModel {

    std::set<std::shared_ptr<GraphicsEngine::Object3D>> Game::nextChunk() {
        std::set<std::shared_ptr<GraphicsEngine::Object3D>> newObjectsToLoadInScene;
        m_chunkBuffer.front()->translate(-BUFFER_CHUNK_HIDING_PLACE);
        newObjectsToLoadInScene = m_chunkBuffer.front()->objects();
        m_terrain.loadChunk(m_chunkBuffer.front());
        m_chunkBuffer.pop();
        
        CardinalDirections previousOrientation = m_terrain.facing();
        m_terrain.nextChunk();

        if (previousOrientation != m_terrain.facing())
            m_player.resetPosition();
        m_chunkCycle ++;
        return newObjectsToLoadInScene;
    }


    void Game::updateEnemy(const glm::vec3 &terrainMovement) {
        m_enemyOffset.push(terrainMovement);
        if (m_enemyOffset.size() > m_player.life()) do {
            m_enemy->globalTranslate(m_enemyOffset.back() - m_enemyOffset.front());
            m_enemyOffset.pop();
        } while(m_enemyOffset.size() < m_player.life());
    }


    std::set<std::shared_ptr<GraphicsEngine::Object3D>> Game::update() {
        std::set<std::shared_ptr<GraphicsEngine::Object3D>> newObjectsToLoadInScene;

        // compute current chunk progress
        m_chunkframe = (m_chunkframe + 1) % m_UPDATES_PER_CHUNK;

        m_player.update();

        // when chunk frame loops back to 0, we move to the next chunk
        if(m_player.life() > 0) {
            if (m_chunkframe == 0) {
                m_terrain.entityAt(m_player.position())->lastVisit(m_player);
                newObjectsToLoadInScene = nextChunk();
            }
            updateEnemy(m_terrain.progress(1.f/m_UPDATES_PER_CHUNK));
        } else {
            if (m_playerDeathCallback) m_playerDeathCallback();
        }

        m_terrain.entityAt(m_player.position())->action(m_player);
        return newObjectsToLoadInScene;
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


    void Game::loadInChunkBuffer(Chunk* newBufferChunk) {
        newBufferChunk->translate(BUFFER_CHUNK_HIDING_PLACE);
        m_chunkBuffer.push(newBufferChunk);
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
