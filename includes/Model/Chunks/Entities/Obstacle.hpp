//
//  Obstacle.hpp
//  Projet_S2_CG_CPP
//
//  Created by Pierre Gabory on 02/01/2019.
//  Copyright © 2019 Pierre Gabory. All rights reserved.
//

#ifndef Obstacle_hpp
#define Obstacle_hpp

#include "Entity.hpp"
namespace GameModel {

    class Obstacle : public Entity {
    protected:
        // rotation animations of player and camera.
        GraphicsEngine::Animation m_playerDamageAnimation;
        GraphicsEngine::Animation m_cameraDamageAnimation;

        void callDamageAnimations() {
            m_playerDamageAnimation.begin();
            m_cameraDamageAnimation.begin();
        }

    public:
        Obstacle(std::shared_ptr<GraphicsEngine::Animatable> &playerAnimatable, std::shared_ptr<GraphicsEngine::Animatable> &cameraAnimatable):
        Entity(), m_playerDamageAnimation(GraphicsEngine::makeDamageBlinkAnimation(playerAnimatable, 30))
        {}
    };
}
#endif /* Obstacle_hpp */
