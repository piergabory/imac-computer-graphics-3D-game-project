#include "Wall.hpp"

namespace GameModel {

	void Wall::firstVisit(Player& player) {
        //Player lose half of his life if he hits a wall
        if ( player.status() != Status::JUMPING) {
			player.incrementLife(-50);
            callDamageAnimations();
		};
	}


    std::unique_ptr<GraphicsEngine::Object3D> Wall::s_entityObject;

    void Wall::loadObject() {
        s_entityObject = std::unique_ptr<GraphicsEngine::Object3D>(makeObject("assets/models/cube_wall.obj", "assets/textures/cubemap_wall.png", "shaders/perspective.vs.glsl", "shaders/flatTexture.fs.glsl"));
    }
    
}