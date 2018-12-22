#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include <set>
#include <memory>
#include <cstddef>// nullptr
#include <glm/glm.hpp> //verctors
#include <ctime> //time in moovePlayer

#include "GraphicsEngine.hpp"
#include "EventObservers.hpp"
#include "Object.hpp"
#include "Animation.hpp"

enum class Direction: char { LEFT, RIGHT};
enum class Position { LEFT, MIDDLE, RIGHT };
enum class Status { STANDING, JUMPING, CROUCHING };

class Player : Events::KeyboardEventObserver {
private:

    const float LANE_WIDTH = 9.f;
    const float JUMP_HEIGHT = 6.f;
    const float CROUCH_HEIGHT = 0.8;

    const uint TRANSLATE_FRAMETIME = 30;
    const uint JUMP_FRAMETIME = 90;
    const uint CROUCH_FRAMETIME = 10;

    Position m_position = Position::MIDDLE;
    Status m_status = Status::STANDING;

    std::shared_ptr<GraphicsEngine::Object3D> m_characterModel;   //eventuelement changer avec un MooveObject

    GraphicsEngine::Animation m_jumpingAnimation;
    GraphicsEngine::Animation m_crouchingAnimation;
    GraphicsEngine::Animation m_standingAnimation;

    GraphicsEngine::Animation m_moveToLeftLaneAnimation;
    GraphicsEngine::Animation m_moveToMiddleLaneAnimation;
    GraphicsEngine::Animation m_moveToRightLaneAnimation;

    void changeLane(const Position &to);

public:
    Player(std::shared_ptr<GraphicsEngine::Object3D> obj);
    ~Player() {};

    inline const std::shared_ptr<GraphicsEngine::Object3D>& model() const {
        return m_characterModel;
    }

    void jump();

    void crouch();

    void move(const Direction &direction);

 };

#endif
