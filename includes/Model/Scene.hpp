#pragma once

#include "Step.hpp"
#include "Player.hpp" 

#include "Entity.hpp"
#include "Jump.hpp"
#include "Slide.hpp"
#include "Wall.hpp"
#include "Turn.hpp"
#include "Coin.hpp"
#include "PowerUp.hpp"

#include <vector>

namespace IMAC2_CG
{
	class Scene
	{
	public:
        // Constructor / Destructor
		Scene(const Player &player)
			: m_player(player) {}
	
        ~Scene() {}
        
        //Getter
        inline const Player player() const {return m_player;}
        
        //Methods
        void addNextStep(Step step) {
            m_terrain.push_back(step);
        }
        void tour(); 

	private:
		std::vector<Step> m_terrain;
        Player m_player;
	};
}
