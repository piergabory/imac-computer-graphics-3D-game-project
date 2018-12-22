#include "Player.hpp"

Player::Player(std::shared_ptr<GraphicsEngine::Object3D> obj):
    m_characterModel(obj)
{}

void Player::translate(const Direction &to) {
    char direction = static_cast<char>(to);
    if(abs(position + direction) <= 1) {
        position += direction;
        m_characterModel->translate(glm::vec3(direction * 3.0,0,0));
    }
}
