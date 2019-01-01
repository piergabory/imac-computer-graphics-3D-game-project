#include "Jump.hpp"

namespace GameModel
{
	void Jump::action(Player& player) {
		//Player dies if he falls intro a pit
        std::cout << "Vous arrivez devant une fosse !" << std::endl;
        
         if ( player.status() != Status::JUMPING) {
			player.incrementLife(-10000);
		};
	}
}
