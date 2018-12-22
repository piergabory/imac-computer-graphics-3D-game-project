#include "Animation.hpp"

namespace GraphicsEngine {
    std::set<Animation*> Animation::s_activeAnimations;
    void Animation::updateAnimations() {
        for (Animation* animation : s_activeAnimations) {
            animation->animateNextFrame();
        }
    };

    Animation::Animation(const std::shared_ptr<Object3D> &object, const uint duration, const glm::vec3 &position, const std::function<void(const std::shared_ptr<Object3D>&,const glm::vec3&, const float)> &interpolation):
        m_pObjectToMove(object),
        m_duration(duration),
    m_targetPositon(position),
        m_interpolationFunction(interpolation) {}

    void Animation::animateNextFrame() {
        if (m_currentFrame == 0) return;
        m_currentFrame--;
        
        std::shared_ptr<GraphicsEngine::Object3D> objectToMove = m_pObjectToMove.lock();
        m_interpolationFunction(objectToMove, m_targetPositon, 1.f / m_duration);
    }

    Animation makeLinearTranslation(const std::shared_ptr<Object3D> &object, const uint duration, const glm::vec3 &position) {
        return Animation(object, duration, position, [](const std::shared_ptr<Object3D> &object,const glm::vec3 &position, const float step) -> void {
            object->translate((position - object->position()) * step);
        });
    }
}

