#include "Slide.hpp"

namespace GameModel {
	void Slide::action(Player& player) {
        //Player lose half of his life if he hits an arch
        std::cout << "Vous arrivez devant une arche !" << std::endl;
        
        if ( player.status() != Status::CROUCHING) {
			player.incrementLife(-50);
		};
	}
}
