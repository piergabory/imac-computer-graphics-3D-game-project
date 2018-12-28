/**
 * \file Terrain.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Terrain_hpp
#define Terrain_hpp

#include <deque>

#include "Chunk.hpp"
#include "TurningChunk.hpp"

enum class CardinalDirections : int {
    NORTH = 0,
    EAST = 90,
    SOUTH = 180,
    WEST = -90
};

class Terrain {
private:
    const uint m_CHUNK_COUNT_AFTER_PLAYER = 5;
    std::deque< std::unique_ptr<Chunk> > m_chunks;
    float m_nextLoadedChunkOrientation = 0;
    glm::vec3 m_nextLoadedChunkPosition = glm::vec3(0.f,0.f,0.f);

    inline const std::unique_ptr<Chunk>& activeChunk() const { return m_chunks[m_CHUNK_COUNT_AFTER_PLAYER]; }

    inline std::unique_ptr<Chunk>& activeChunk() { return m_chunks[m_CHUNK_COUNT_AFTER_PLAYER]; }

public:
    inline void nextChunk() {
        m_chunks.pop_front();
        activeChunk()->onEnter();
    }

    const CardinalDirections facing() const;

    void enterChunk(Player &player);
    void testAction(Player &player);

    void loadChunk(Chunk *chunkToLoad);

    void progress(const float progress);

    Terrain() {}
    
    ~Terrain() {}
};


#endif /* Terrain_hpp */
