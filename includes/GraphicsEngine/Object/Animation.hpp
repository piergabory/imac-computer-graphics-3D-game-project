#ifndef Animation_hpp
#define Animation_hpp

#include <memory>
#include <functional>
#include <set>
#include <cmath>
#include "Object3D.hpp"

namespace GraphicsEngine {
    class Animation {
    private:
        const std::weak_ptr<GraphicsEngine::Object3D> m_pObjectToMove;
        const uint m_duration;
        const glm::vec3 m_targetPositon;
        const std::function<void(const std::shared_ptr<GraphicsEngine::Object3D>&,const glm::vec3&, const float, const float)> m_interpolationFunction;

        uint m_currentFrame = 0;

        static std::set<Animation*> s_activeAnimations;

        void animateNextFrame();

    public:

        inline void begin() {
            m_currentFrame = m_duration;
            s_activeAnimations.insert(this);
        }

        inline void cancel() {
            m_currentFrame = 0;
            s_activeAnimations.erase(this);
        }


        static void updateAnimations();

        Animation(const std::shared_ptr<Object3D> &object, const uint duration, const glm::vec3 &position, const std::function<void(const std::shared_ptr<Object3D>&,const glm::vec3&,const  float, const float)> &interpolation);
    };

    Animation makeLinearTranslation(const std::shared_ptr<Object3D> &object, const uint duration, const glm::vec3 &position);

    Animation makeBounceAnimation(const std::shared_ptr<Object3D> &object, const uint duration, const float height);
}


#endif /* Animation_hpp */
