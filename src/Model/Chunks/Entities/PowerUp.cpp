#include "PowerUp.hpp"

namespace GameModel
{
	void PowerUp::action(Player& player) {
        //Player regains life if he catches a power up
        std::cout << "Vous distancez les singes démoniaques !" << std::endl;
		player.incrementLife(50);
	}
}
