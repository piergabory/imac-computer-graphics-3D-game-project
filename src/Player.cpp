#include "Player.hpp"

Player::Player(std::shared_ptr<GraphicsEngine::Object3D> obj):
    m_characterModel(obj),
    m_jumpingAnimation(GraphicsEngine::makeBounceAnimation(m_characterModel, JUMP_FRAMETIME, JUMP_HEIGHT)),
    m_crouchingAnimation(GraphicsEngine::makeCrouchAnimation(m_characterModel, CROUCH_FRAMETIME, CROUCH_HEIGHT)),
    m_standingAnimation(GraphicsEngine::makeUnCrouchAnimation(m_characterModel, CROUCH_FRAMETIME, CROUCH_HEIGHT)),
    m_moveToLeftLaneAnimation(GraphicsEngine::makeLinearTranslation(m_characterModel, TRANSLATE_FRAMETIME, glm::vec3(-LANE_WIDTH,0.f,0.f))),
    m_moveToMiddleLaneAnimation(GraphicsEngine::makeLinearTranslation(m_characterModel, TRANSLATE_FRAMETIME, glm::vec3(0.f,0.f,0.f))),
    m_moveToRightLaneAnimation(GraphicsEngine::makeLinearTranslation(m_characterModel, TRANSLATE_FRAMETIME, glm::vec3(LANE_WIDTH,0.f,0.f)))
{}

void Player::jump() {
    if (m_status != Status::STANDING) return;
    m_jumpingAnimation.whenDone([=]() -> void { m_status = Status::STANDING; });
    m_status = Status::JUMPING;
    m_jumpingAnimation.begin();
}

void Player::crouch() {
    if (m_status == Status::STANDING) {
        m_status = Status::CROUCHING;
        m_crouchingAnimation.begin();
    } else if (m_status == Status::CROUCHING){
        m_status = Status::STANDING;
        m_standingAnimation.begin();
    }
}

void Player::move(const Direction &direction) {
    switch (m_position) {
        case Position::LEFT:
            if(direction == Direction::RIGHT) {
                m_position = Position::MIDDLE;
                m_moveToMiddleLaneAnimation.begin();
            }
            break;

        case Position::MIDDLE:
            if(direction == Direction::LEFT) {
                m_position = Position::LEFT;
                m_moveToLeftLaneAnimation.begin();
            }
            if(direction == Direction::RIGHT) {
                m_position = Position::RIGHT;
                m_moveToRightLaneAnimation.begin();
            }
            break;

        case Position::RIGHT:
            if(direction == Direction::LEFT) {
                m_position = Position::MIDDLE;
                m_moveToMiddleLaneAnimation.begin();
            }
            break;

        default: assert(false && "Unknown Position");
    }
};

