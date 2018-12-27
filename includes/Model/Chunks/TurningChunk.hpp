#ifndef TurningChunk_hpp
#define TurningChunk_hpp

#include "Camera.hpp"
#include "Chunk.hpp"

class TurningChunk : public Chunk {
    const TurnDirection m_direction;
    GraphicsEngine::Animation m_cameraAnimation;

public:
    inline virtual const glm::vec3 exitPosition() const {
        switch(m_direction) {
            case TurnDirection::LEFT: return glm::vec3(-3,0,3);
            case TurnDirection::RIGHT: return glm::vec3(3,0,3);
        }
    }

    inline virtual const float exitOrientation() const { return glm::radians((float)m_direction); }

    inline virtual void onEnter() { m_cameraAnimation.begin(); }

    // constructor
    TurningChunk(TurnDirection direction, std::shared_ptr<GraphicsEngine::Camera> cameraToControlOnTurn):
    Chunk(new Turn(direction), new Turn(direction), new Turn(direction)),
    m_direction(direction),
    m_cameraAnimation(GraphicsEngine::makeCameraTurn(cameraToControlOnTurn, 20, glm::radians((float) direction)))
    {}

    // copy constructor
    TurningChunk(TurningChunk& source): Chunk(source), m_direction(source.m_direction), m_cameraAnimation(source.m_cameraAnimation) {}

    ~TurningChunk() {}
};

#endif /* TurningChunk_hpp */
