#pragma once

#include "Entity.hpp"

namespace GameModel
{
	class Wall : public Entity
	{
	public:
		//Constructor / destructor
		Wall() {}
		~Wall() {}

		//Methods
		void action(Player& player) override;
	};
}
