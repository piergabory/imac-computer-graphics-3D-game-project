#ifndef TurningChunk_hpp
#define TurningChunk_hpp

#include "Chunk.hpp"

class TurningChunk : public Chunk {
    const TurnDirection m_direction;

public:
    inline virtual const glm::vec3 exitPosition() const {
        switch(m_direction) {
            case TurnDirection::LEFT: return glm::vec3(-3,0,3);
            case TurnDirection::RIGHT: return glm::vec3(3,0,3);
        }
    }
    inline virtual const float exitOrientation() const { return glm::radians((float)m_direction); }

    // constructor
    TurningChunk(TurnDirection direction): Chunk(new Turn(direction), new Turn(direction), new Turn(direction)),
    m_direction(direction)
    {}

    // copy constructor
    TurningChunk(TurningChunk& source): Chunk(source), m_direction(source.m_direction) {}

    ~TurningChunk() {}
};

#endif /* TurningChunk_hpp */
