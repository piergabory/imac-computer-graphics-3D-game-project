#ifndef TurningChunk_hpp
#define TurningChunk_hpp

#include "Chunk.hpp"

class TurningChunk : public Chunk {
    const TurnDirection m_direction;

public:

    // constructor
    TurningChunk(TurnDirection direction): Chunk(new Turn(direction), new Turn(direction), new Turn(direction)),
    m_direction(direction)
    {}

    // copy constructor
    TurningChunk(TurningChunk& source): Chunk(source), m_direction(source.m_direction) {}
};

#endif /* TurningChunk_hpp */
