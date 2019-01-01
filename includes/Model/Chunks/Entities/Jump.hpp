#pragma once

#include "Entity.hpp"

namespace GameModel
{
	class Jump : public Entity
	{
	public:
		//Constructor / destructor
		Jump() {}
		~Jump() {}

		//Methods
		void action(Player& player) override;
	};
}
