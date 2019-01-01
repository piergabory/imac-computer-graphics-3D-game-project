#include "Coin.hpp"

namespace GameModel
{
	void Coin::action(Player& player) const
	{
        //Player gains points if he catches a coin
        std::cout << "Vous gagnez cinq points !" << std::endl;
		player.incrementScore(5);
	}
    
    std::string Coin::display() const
    {
        std::string name = "Coin";
        return name;
    }
}
