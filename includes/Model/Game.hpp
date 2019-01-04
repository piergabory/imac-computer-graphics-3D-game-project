/**
 * \file Game.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Game_hpp
#define Game_hpp
#pragma once

#include <queue>

#include "Player.hpp"
#include "Terrain.hpp"

#include "ImportedMesh.hpp"

namespace GameModel {

    /// game controls, to be mapped on keyboard or game controller in GameController
    enum class Controls { LEFT, RIGHT, UP, DOWN };

    /**
     * GAME CLASS
     *
     * \brief Central controller class, Handles communication between Model classes and the GameController
     */
    class Game{

    private:

        // parameters

        /// \brief defines the game rythm
        const unsigned int m_UPDATES_PER_CHUNK = 10;

        // progress in the current chunk
        unsigned int m_chunkframe = 0;

        // passed chunk count
        unsigned long int m_chunkCycle = 0;

        // buffer chunks are translated out of view until they're loaded in terrain
        const glm::vec3 BUFFER_CHUNK_HIDING_PLACE = glm::vec3(1000);


        // data

        /// \brief Player instance
        Player m_player;

        /// \brief Terrain instance
        Terrain m_terrain;

        /// \brief scene enemy object handle
        std::shared_ptr<GraphicsEngine::Object3D> m_enemy;


        // buffers

        /// \brief contains all the transformations the enemy has to perform to catch up with the player
        /// If size is zero, the enemy is on the player model
        std::queue<glm::vec3> m_enemyOffset;

        /// \brief pile of chunks to be loaded in terrain
        std::queue<Chunk*> m_chunkBuffer;


        // private methods

        /// \brief shifts the terrain to the next chunk.
        /// Moves the player back to the center on each turn.
        std::set<std::shared_ptr<GraphicsEngine::Object3D>> nextChunk();


        /// \todo doc
        void updateEnemy(const glm::vec3 &terrainMovement);


        // static initializers

        /// \brief Static method generating the player's character object.
        static std::shared_ptr<GraphicsEngine::Object3D> loadPlayerObject();

        /// \brief Static method generating the enemy object
        static std::shared_ptr<GraphicsEngine::Object3D> loadEnemyObject();

    public:

        // public methods

        /// \brief frame, gameloop update
        std::set<std::shared_ptr<GraphicsEngine::Object3D>> update();

        /// \brief Redirects controller inputs on player movements, attacks, bonuses etc...
        void callInput(Controls control);

        void loadInChunkBuffer(Chunk* newBufferChunk);

        // getter

        /// \brief getter on the character model
        inline std::shared_ptr<GraphicsEngine::Object3D> playerModel() const { return m_player.model(); }

        /// \brief getter on the enemy model
        inline std::shared_ptr<GraphicsEngine::Object3D> enemyModel() const { return m_enemy; }

        /// \brief getter on the terrain
        inline Terrain& terrain() { return m_terrain; }
        inline const Terrain& terrain() const { return m_terrain; }


        // constructor

        /// \brief constructor
        Game();

        /// \brief destructor
        ~Game();
    };

}

#endif /* Game_hpp */
