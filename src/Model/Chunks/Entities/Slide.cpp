#include "Slide.hpp"

namespace GameModel {

	void Slide::firstVisit(Player& player) {
        //Player lose half of his life if he hits an arch
        if ( player.status() != Status::CROUCHING) {
			player.incrementLife(-m_DAMAGE);
            callDamageAnimations();
		};
	}


    std::unique_ptr<GraphicsEngine::Object3D> Slide::s_entityObject;

    void Slide::loadObject() {
        s_entityObject = std::unique_ptr<GraphicsEngine::Object3D>(makeObject("assets/models/road_crouch.obj", "assets/textures/road_crouch.png", "shaders/perspective.vs.glsl", "shaders/lighting.fs.glsl"));
    }
    
}
