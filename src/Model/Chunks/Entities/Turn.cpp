
#include "Turn.hpp"

std::unique_ptr<GraphicsEngine::Object3D> Turn::s_turnObjectLeftVariant;
std::unique_ptr<GraphicsEngine::Object3D> Turn::s_turnObjectRightVariant;

void Turn::loadObjects() {
    s_turnObjectLeftVariant = std::unique_ptr<GraphicsEngine::Object3D>(Entity::makeObject("assets/models/turn.obj", "assets/textures/cubemap_left_turn.png", "shaders/perspective.vs.glsl", "shaders/flatTexture.fs.glsl"));

    s_turnObjectRightVariant = std::unique_ptr<GraphicsEngine::Object3D>(Entity::makeObject("assets/models/turn.obj", "assets/textures/cubemap_right_turn.png", "shaders/perspective.vs.glsl", "shaders/flatTexture.fs.glsl"));
}
