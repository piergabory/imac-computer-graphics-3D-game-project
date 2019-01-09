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

        m_enemyMoves.back().w = glm::radians((float)m_terrain.facing() - (float)previousOrientation) / m_UPDATES_PER_CHUNK;

        return newObjectsToLoadInScene;
    }



    void Game::updateEnemy(const glm::vec3 &terrainMovement) {
        if(m_enemyMoves.empty()) return;

        if(m_enemyMoves.size() * 5 < m_player.life()) {
            m_enemyMoves.push_back(glm::vec4(terrainMovement,m_enemyMoves.back().w));
        }

        if(m_enemyMoves.size() * 5 >= m_player.life()) m_enemyMoves.pop_front();

        // place enemy on player
        m_enemy->place(glm::vec3(0,0,0));

        // move back in place using the move pile
        // dirty but robust technique. the position is reset relative to the player every time.
        for (glm::vec4 move : m_enemyMoves) {
            m_enemy->globalTranslate(glm::vec3(move));
        }

        // rotates the enemy in turns.
        m_enemy->rotate(m_enemyMoves.front().w , glm::vec3(0,1,0));
    }


    std::set<std::shared_ptr<GraphicsEngine::Object3D>> Game::update() {
        std::set<std::shared_ptr<GraphicsEngine::Object3D>> newObjectsToLoadInScene;

        // compute current chunk progress
        m_chunkframe = (m_chunkframe + 1) % m_UPDATES_PER_CHUNK;

        m_player.update();

        glm::vec3 move(0);
        if (m_player.life() > 0)
            move = m_terrain.progress(1.f/m_UPDATES_PER_CHUNK);

        // when chunk frame loops back to 0, we move to the next chunk
        updateEnemy(move);
        if(m_player.life() > 0) {
            if (m_chunkframe == 0) {
                m_terrain.entityAt(m_player.position())->lastVisit(m_player);
                newObjectsToLoadInScene = nextChunk();
            }
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
    {
        m_enemyMoves.emplace_back(0);
    }

    
    // destructor
    Game::~Game() {}

    

    // static method generating player character models
    std::shared_ptr<GraphicsEngine::Object3D> Game::loadPlayerObject() {

        // define resources paths
        const GraphicsEngine::LocalFilePath
        PLAYER_MESH("assets/models/player.obj"),
        PLAYER_TEXTURE("assets/textures/player.png"),
        VERTEX_SHADER("shaders/perspective.vs.glsl"),
        FRAGMENT_SHADER("shaders/lighting.fs.glsl");

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
        PLAYER_MESH("assets/models/enemy.obj"),
        PLAYER_TEXTURE("assets/textures/enemy.png"),
        VERTEX_SHADER("shaders/perspective.vs.glsl"),
        FRAGMENT_SHADER("shaders/lighting.fs.glsl");

        // creates player character model
        std::shared_ptr<GraphicsEngine::ShaderProgram> playerShader = std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(VERTEX_SHADER, FRAGMENT_SHADER);
        std::shared_ptr<GraphicsEngine::Texture> playerTexture = std::make_shared<GraphicsEngine::Texture>(PLAYER_TEXTURE);
        std::shared_ptr<GraphicsEngine::Material> playerMaterial = std::make_shared<GraphicsEngine::Material>(playerShader, playerTexture);
        std::shared_ptr<GraphicsEngine::Mesh3D> playerMesh = std::make_shared<GraphicsEngine::ImportedMesh>(PLAYER_MESH);
        return std::make_shared<GraphicsEngine::Object3D>(playerMesh, playerMaterial);
    }

}
