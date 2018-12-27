#ifndef Animation_hpp
#define Animation_hpp

#include <memory>
#include <functional>
#include <vector>
#include <cmath>
#include "Object3D.hpp"

namespace GraphicsEngine {
    class Animation {
    private:
        const std::weak_ptr<GraphicsEngine::Object3D> m_pObjectToMove;
        const uint m_duration;
        const glm::vec3 m_targetPositon;
        const std::function<void(const std::shared_ptr<GraphicsEngine::Object3D>&,const glm::vec3&, const float, const float)> m_interpolationFunction;
        std::function<void(void)> m_callback;

        uint m_currentFrame = 0;

        static std::vector<Animation*> s_activeAnimations;

        bool animateNextFrame();

    public:

        inline void begin() {
            m_currentFrame = m_duration;
            s_activeAnimations.push_back(this);
        }

        inline void cancel() {
            m_callback();
            m_currentFrame = 0;
            for (size_t i = 0; i < s_activeAnimations.size(); i++) {
                if (s_activeAnimations[i] == this)
                    s_activeAnimations.erase(s_activeAnimations.begin() + i);
            }
        }

        inline void whenDone(const std::function<void(void)> &callback) {
            m_callback = callback;
        }

        static void updateAnimations();

        Animation(const std::shared_ptr<Object3D> &object, const uint duration, const glm::vec3 &position, const std::function<void(const std::shared_ptr<Object3D>&,const glm::vec3&,const  float, const float)> &interpolation);
    };

    Animation makeLinearTranslation(const std::shared_ptr<Object3D> &object, const uint duration, const glm::vec3 &position);

    Animation makeBounceAnimation(const std::shared_ptr<Object3D> &object, const uint duration, const float height);

    Animation makeCrouchAnimation(const std::shared_ptr<Object3D> &object, const uint duration, const float toHeight);

    Animation makeUnCrouchAnimation(const std::shared_ptr<Object3D> &object, const uint duration, const float fromHeight);
}


#endif /* Animation_hpp */
