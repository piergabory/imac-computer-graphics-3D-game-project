/**
 * \file Animation.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Animation_hpp
#define Animation_hpp

#include <memory>
#include <functional>
#include <vector>
#include <cmath>

#include <glm/glm.hpp>

namespace GraphicsEngine {

    /**
     * ANIMATABLE INTERFACE
     *
     * \brief Interface implemented by movable objects
     * such as lights, cameras or 3D objects in a scene.
     * Animatable can be modified by the animation class for fluid movements.
     * Abstract class
     */
    struct Animatable {
        // getters
        virtual inline const glm::vec3 position() const = 0;

        // transformation methods
        virtual void translate(const glm::vec3& direction) = 0;
        virtual void place(const glm::vec3& direction) = 0;
        virtual void rotate(const float angle, const glm::vec3 &direction) = 0;
        virtual void scale(const glm::vec3 &scalingVector) {};

        // virtual destructor
        virtual ~Animatable() {}
    };



    /**
     * ANIMATION CLASS
     *
     * \brief Transforms an animatable over time using a given interpolation function
     * Will call back another given function when done.
     */
    class Animation {
    private:

        /// \brief Shared pointer on the Animatable object.
        /// \warning Animatable shouldn't have any reference to Animation (memory leak)
        /// Pointer is destroyed at the end of animation, if the object is forgotten during the animation, it will stay on screen until the animation reaches its end.
        const std::shared_ptr<Animatable> m_pObjectToMove;

        /// \brief duration of the animation in frames.
        const unsigned int m_duration;

        /// \brief progress of the animation in frames.
        /// counting down from the total frame count
        unsigned int m_currentFrame = 0;

        /// \brief containers of informations of the final state of the animation.
        /// \todo this is never used as a position vector. but often contains angles, height targets, Y axis position targets, translation vector ect... Maybe should be changed to const std::vector<const float>
        const glm::vec3 m_targetPositon;

        /// \brief interpolation function used to calculate the animatable transformation on each frame
        /// Recieves in paramerters, reference value of the animatable, informations for the final state, value of the progress of the animation (between 0 and 1) and stepping of the animation (on the same scale)
        const std::function<void(Animatable&,const glm::vec3&, const float, const float)> m_interpolationFunction;

        /// \brief optional callback called after the animation reaches its last frame.
        std::function<void(void)> m_callback;

        /// \brief updates the animatable for the next frame. Destroys the animation if it has reached the end.
        bool animateNextFrame();

        /// \brief static container of all the current animations to be updated in the game loop.
        static std::vector<Animation*> s_activeAnimations;


    public:
        /// \brief Launches animation
        /// Adds the animation to the static collection and reset the progress to zero.
        void begin();

        /// \brief Stops the animation.
        /// current frame is set back to zero. the animation is removed from the update loop.
        void cancel();

        /// \brief Animation end callback setter
        inline void whenDone(const std::function<void(void)> &callback) {
            m_callback = callback;
        }

        /// \brief update each animation in the static collection.
        /// To be called in each game loop call
        static void updateAnimations();

        /// \brief constructor
        Animation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const glm::vec3 &position, const std::function<void(Animatable& ,const glm::vec3&,const  float, const float)> &interpolation);

    };


    // Factories of Animations
    Animation makeLinearPlace(const std::shared_ptr<Animatable> &object, const unsigned int duration, const glm::vec3 &position);
    Animation makeLinearTranslation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const glm::vec3 &position);
    Animation makeBounceAnimation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const float height);
    Animation makeCrouchAnimation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const float toHeight);
    Animation makeUnCrouchAnimation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const float fromHeight);
    Animation makeTurnAnimation(const std::shared_ptr<Animatable> &camera, unsigned int duration, const float angle);

}


#endif /* Animation_hpp */
