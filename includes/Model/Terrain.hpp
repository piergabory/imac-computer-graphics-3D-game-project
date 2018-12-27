/**
 * \file Terrain.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Terrain_hpp
#define Terrain_hpp

#include <list>

#include "Chunk.hpp"
#include "TurningChunk.hpp"

class Terrain {
private:
    std::list< std::unique_ptr<Chunk> > m_chunks;
    float m_nextLoadedChunkOrientation = 0;
    glm::vec3 m_nextLoadedChunkPosition = glm::vec3(0.f,0.f,0.f);

public:
    inline void nextChunk() { m_chunks.pop_front(); }

    void testAction(Player &player);

    void loadChunk(Chunk *chunkToLoad);

    void progress(const float progress);

    Terrain() {}
    
    ~Terrain() {}
};


#endif /* Terrain_hpp */
