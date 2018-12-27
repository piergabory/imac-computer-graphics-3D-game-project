#ifndef Turn_hpp
#define Turn_hpp

#include "Entity.hpp"
#include "Animation.hpp"

enum class TurnDirection : int {
    LEFT = -90, RIGHT = 90
};

class Turn : public Entity {
private:
    static std::unique_ptr<GraphicsEngine::Object3D> s_turnObjectLeftVariant;
    static std::unique_ptr<GraphicsEngine::Object3D> s_turnObjectRightVariant;

    GraphicsEngine::Animation m_playerTurnAnimation;
    GraphicsEngine::Animation m_cameraTurnAnimation;

public:
    void action() override {}

    void onEnter() override { m_playerTurnAnimation.begin(); m_cameraTurnAnimation.begin(); }

    static void loadObjects();

    Turn(TurnDirection direction, std::shared_ptr<GraphicsEngine::Animatable> &playerAnimatable, std::shared_ptr<GraphicsEngine::Animatable> &cameraAnimatable):
        Entity(),
        m_playerTurnAnimation(GraphicsEngine::makeTurnAnimation(playerAnimatable, 20, glm::radians((float)direction))),
        m_cameraTurnAnimation(GraphicsEngine::makeTurnAnimation(cameraAnimatable, 20, glm::radians((float)direction)))
    {
        if (s_turnObjectLeftVariant == nullptr || s_turnObjectRightVariant == nullptr) loadObjects();

        switch (direction) {
            case TurnDirection::LEFT:
                m_entityObject = std::make_shared<GraphicsEngine::Object3D>(*s_turnObjectLeftVariant);
                break;

            case TurnDirection::RIGHT:
                m_entityObject = std::make_shared<GraphicsEngine::Object3D>(*s_turnObjectRightVariant);
                break;

            default: assert(false && "Bad turn direction");
        }
    }

    ~Turn() override {};
};

#endif /* Turn_hpp */
