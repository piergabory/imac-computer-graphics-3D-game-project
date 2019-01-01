#include "Jump.hpp"

namespace GameModel
{
	void Jump::firstVisit(Player& player) {
		//Player dies if he falls intro a pit
        std::cout << "Vous arrivez devant une fosse !" << std::endl;
        
         if ( player.status() != Status::JUMPING) {
			player.incrementLife(-10000);
		};
	}


    std::unique_ptr<GraphicsEngine::Object3D> Jump::s_entityObject;

    void Jump::loadObject() {
        s_entityObject = std::unique_ptr<GraphicsEngine::Object3D>(makeObject("assets/models/cube_jump.obj", "assets/textures/cubemap_jump.png", "shaders/perspective.vs.glsl", "shaders/flatTexture.fs.glsl"));
    }
}
