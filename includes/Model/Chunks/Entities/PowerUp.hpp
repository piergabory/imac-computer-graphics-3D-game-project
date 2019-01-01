#pragma once

#include "Entity.hpp"

namespace GameModel
{
	class PowerUp : public Entity
	{
	public:
		//Constructor / destructor
		PowerUp() {}
		~PowerUp() {}

		//Methods
		void action(Player& player) override;
	};
}
