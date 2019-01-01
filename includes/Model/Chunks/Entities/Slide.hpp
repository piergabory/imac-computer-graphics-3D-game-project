#pragma once

#include "Entity.hpp"

namespace GameModel
{
	class Slide : public Entity
	{
	public:
		//Constructor / destructor
		Slide() {}
		~Slide() {}

		//Methods
		void action(Player& player) override;
	};
}
