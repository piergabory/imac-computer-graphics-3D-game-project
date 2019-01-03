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
        /// \brief Player instance
        Player m_player;

        /// \brief Terrain instance
        Terrain m_terrain;

        /// \brief scene enemy object handle
        std::shared_ptr<GraphicsEngine::Object3D> m_enemy;

        /// \brief contains all the transformations the enemy has to perform to catch up with the player
        /// If size is zero, the enemy is on the player model
        std::queue<glm::vec3> m_enemyOffset;

        /// \brief Static method generating the player's character object.
        static std::shared_ptr<GraphicsEngine::Object3D> loadPlayerObject();

        /// \brief Static method generating the enemy object
        static std::shared_ptr<GraphicsEngine::Object3D> loadEnemyObject();


    public:

        /// \brief getter on the character model
        inline std::shared_ptr<GraphicsEngine::Object3D> playerModel() const { return m_player.model(); }
        /// \brief getter on the enemy model
        inline std::shared_ptr<GraphicsEngine::Object3D> enemyModel() const { return m_enemy; }

        /// \brief getter on the terrain
        inline Terrain& terrain() { return m_terrain; }
        inline const Terrain& terrain() const { return m_terrain; }

        /// \brief frame, gameloop update
        void update(float chunkProgress);

        /// \brief shifts the terrain to the next chunk.
        /// Moves the player back to the center on each turn.
        /// \param takes the next chunk to be pushed at the end of the terrain.
        void nextChunk(Chunk* newChunk);

        /// \brief Redirects controller inputs on player movements, attacks, bonuses etc...
        void callInput(Controls control);

        /// \brief constructor
        Game();

        /// \brief destructor
        ~Game();
    };

}

#endif /* Game_hpp */
