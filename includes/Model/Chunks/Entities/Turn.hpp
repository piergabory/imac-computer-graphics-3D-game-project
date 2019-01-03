/**
 * \file Turn.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Turn_hpp
#define Turn_hpp
#pragma once

#include "Obstacle.hpp"
#include "Animation.hpp"

namespace GameModel {

    /// \brief Directions enumeration Left or Right
    /// possible improvements: added UP, DOWN, 30°LEFT etc...
    enum class TurnDirection : int {
        LEFT = -90, RIGHT = 90
    };

    /**
     *  TURN CLASS
     *
     *  Entity subclass
     *  \brief Describe entity specialisation for turning chunks of the terrain
     *  \brief turning entities should only appear inside turning chunks
     */
    class Turn final : public Obstacle {
    private:
        // static reference to 3D object of left and right turns
        static std::unique_ptr<GraphicsEngine::Object3D> s_turnObjectLeftVariant;
        static std::unique_ptr<GraphicsEngine::Object3D> s_turnObjectRightVariant;

        TurnDirection m_direction;
        bool m_hasPlayerSuccessfullyPassed = false;

        // rotation animations of player and camera.
        GraphicsEngine::Animation m_playerTurnAnimation;
        GraphicsEngine::Animation m_cameraTurnAnimation;

    public:
        // Entities overrides
        /// \brief repeated tests on the player on each frame
        void lastVisit(Player& player) override;

        void test(Player& player) override;

        /// \brief object factory caller with parameters for an empty object
        /// automagically called on first instanciation of Entity
        static void loadObjects();


        /// \brief constructor
        /// takes the turn direction and reference on animatables of camera and player character.
        Turn(TurnDirection direction, std::shared_ptr<GraphicsEngine::Animatable> &playerAnimatable, std::shared_ptr<GraphicsEngine::Animatable> &cameraAnimatable);
        ~Turn() override {};
    };

}
#endif /* Turn_hpp */
