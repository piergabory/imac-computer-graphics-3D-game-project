#include "Wall.hpp"

namespace GameModel
{
	void Wall::action(Player& player) {
        //Player lose half of his life if he hits a wall
        std::cout << "Vous arrivez devant un mur !" << std::endl;   
        
        if ( player.status() != Status::JUMPING) {
			player.incrementLife(-50);
		};
	}
}
