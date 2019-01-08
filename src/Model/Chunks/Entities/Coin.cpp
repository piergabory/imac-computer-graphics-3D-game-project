#include "Coin.hpp"

namespace GameModel
{
	void Coin::firstVisit(Player& player)
	{
        //Player gains points if he catches a coin
		player.incrementScore(5);
	}

    
    std::unique_ptr<GraphicsEngine::Object3D> Coin::s_entityObject;

    void Coin::loadObject() {
        s_entityObject = std::unique_ptr<GraphicsEngine::Object3D>(makeObject("assets/models/road.obj", "assets/textures/legacy/cubemap_coin.png", "shaders/perspective.vs.glsl", "shaders/flatTexture.fs.glsl"));
    }
}
