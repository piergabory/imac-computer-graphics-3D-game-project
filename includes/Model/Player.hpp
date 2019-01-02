/**
 * \file Player.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Player_hpp
#define Player_hpp
#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "GraphicsEngine.hpp"
#include "EventObservers.hpp"
#include "Animation.hpp"

namespace GameModel {

    // Player characteristics enumerations.
    enum class Direction: char { LEFT, RIGHT};
    enum class Position { LEFT, MIDDLE, RIGHT };
    enum class Status { STANDING, JUMPING, CROUCHING, TURNING_LEFT, TURNING_RIGHT };

    /**
     * PLAYER CLASS
     *
     * \brief Describe the player state and controls character animations.
     */
    class Player {
    private:

        // ANIMATION CONSTANTS

        ///\brief distance the player travels when switching lanes
        const float LANE_WIDTH = 2.f;

        ///\brief Maximum height of the jump (Parabolic curve)
        const float JUMP_HEIGHT = 6.f;

        ///\brief Size reduction of the player when crouching (Y scaling)
        const float CROUCH_HEIGHT = 0.8;

        ///\brief Animations frame count. Game runs at 60 FPS.
        const unsigned int TRANSLATE_FRAMETIME = 20;
        const unsigned int JUMP_FRAMETIME = 30;
        const unsigned int CROUCH_FRAMETIME = 10;

        ///\brief Lane the player is currently running in
        Position m_position = Position::MIDDLE;

        ///\brief Status of the player (running, jumping, crouching)
        /// the player cant jump if jumping or crouching. It can only crouch if standing
        Status m_status = Status::STANDING;

        ///\brief life describes the ability of the player to continue playing the game
        /// Game should stop when this value reaches zero
        unsigned int m_life = 100;
        unsigned int m_score = 0;

        ///\brief pointer to the character 3D object.
        /// This is the main handle on the model, if it's released, the model should be destroyed
        std::shared_ptr<GraphicsEngine::Object3D> m_characterModel;

        ///\brief Character animation. Play the animation using the begin() method.
        GraphicsEngine::Animation m_jumpingAnimation;
        GraphicsEngine::Animation m_crouchingAnimation;
        GraphicsEngine::Animation m_standingAnimation;
        GraphicsEngine::Animation m_moveToLeftLaneAnimation;
        GraphicsEngine::Animation m_moveToRightLaneAnimation;
        GraphicsEngine::Animation m_resetPosition;

    public:
        ///\brief constructor
        Player(std::shared_ptr<GraphicsEngine::Object3D> obj);

        ///\brief destructor
        ~Player() {};

        ///\brief model
        inline const std::shared_ptr<GraphicsEngine::Object3D>& model() const {
            return m_characterModel;
        }

        ///\brief status getter
        inline Status& status() { return m_status; }

        ///\brief changes the player's life. Game over when life reaches zero
        inline void incrementLife(int amount) { m_life += amount; };

        ///\brief updates the player's score.
        inline void incrementScore(unsigned int points) { m_score += points; }

        ///\brief makes the player jump. ignored if called while jumping
        void jump();

        ///\brief Toggles crouching. Player cant crouch if jumping.
        void crouch();

        ///\brief Moves player to the adjacent lane. Ignored if there are no lanes to go to.
        void move(const Direction &direction);

        /// \brief Recenter the player to the center of the scene
        void resetPosition();

        ///\brief Position (Terrain lane) getter
        inline const Position position() const { return m_position; }

        inline const unsigned int life() const { return m_life; }
     };
}
#endif
