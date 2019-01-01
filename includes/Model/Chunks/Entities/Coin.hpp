#pragma once

#include "Entity.hpp"

namespace GameModel
{
	class Coin : public Entity
	{
	public:
		//Constructor / destructor
		Coin() {}
		~Coin() {}
		
		//Methods
		void action(Player &player) const override;
        std::string display() const override;
	};
}
