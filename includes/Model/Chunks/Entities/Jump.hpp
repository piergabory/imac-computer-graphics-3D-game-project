#pragma once

#include "Obstacle.hpp"

namespace GameModel
{
	class Jump final : public Obstacle
	{
    private:
        /// \brief static default entity object.
        /// use this instance to clone new objects
        static std::unique_ptr<GraphicsEngine::Object3D> s_entityObject;

    public:

        /// \brief object factory caller with parameters for an empty object
        /// automagically called on first instanciation of Entity
        static void loadObject();

		//Methods
		void firstVisit(Player& player) override;

        //Constructor / destructor
        Jump(std::shared_ptr<GraphicsEngine::Animatable> playerAnimatable, std::shared_ptr<GraphicsEngine::Animatable> cameraAnimatable) :
        Obstacle(playerAnimatable, cameraAnimatable) {
            if (!s_entityObject) loadObject();
            m_entityObject =  std::make_shared<GraphicsEngine::Object3D>(*s_entityObject);
            GraphicsEngine::Animation m_playerDamageAnimation(GraphicsEngine::makeDeathFallAnimation(playerAnimatable, 30, 10));
        }
        
        ~Jump() {}
	};
}
