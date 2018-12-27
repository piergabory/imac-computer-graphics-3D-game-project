#ifndef Animation_hpp
#define Animation_hpp

#include <memory>
#include <functional>
#include <vector>
#include <cmath>

#include <glm/glm.hpp>

namespace GraphicsEngine {

    // animatable interface
    struct Animatable {
        virtual inline const glm::vec3 position() const = 0;
        virtual void translate(const glm::vec3& direction) = 0;
        virtual void place(const glm::vec3& direction) = 0;
        virtual void rotate(const float angle, const glm::vec3 &direction) = 0;
        virtual void scale(const glm::vec3 &scalingVector) {};
        virtual ~Animatable() {}
    };

    class Animation {
    private:
        const std::weak_ptr<Animatable> m_pObjectToMove;
        const unsigned int m_duration;
        const glm::vec3 m_targetPositon;
        const std::function<void(const std::shared_ptr<Animatable>&,const glm::vec3&, const float, const float)> m_interpolationFunction;
        std::function<void(void)> m_callback;

        unsigned int m_currentFrame = 0;

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

        Animation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const glm::vec3 &position, const std::function<void(const std::shared_ptr<Animatable>&,const glm::vec3&,const  float, const float)> &interpolation);
    };

    Animation makeLinearTranslation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const glm::vec3 &position);

    Animation makeBounceAnimation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const float height);

    Animation makeCrouchAnimation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const float toHeight);

    Animation makeUnCrouchAnimation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const float fromHeight);
}


#endif /* Animation_hpp */
