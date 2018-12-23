/**
 * \file Terrain.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Terrain_hpp
#define Terrain_hpp

#include <queue>
#include <map>

#include "Entity.hpp"
#include "Player.hpp"

class Terrain {

    std::queue< std::map<Position, std::unique_ptr<Entity> > > m_chunks;

public:
    inline void nextChunk() { m_chunks.pop(); }

    void testAction(Player &player);

    void loadChunk(Entity* left, Entity* middle, Entity* right);

    Terrain() {};
    ~Terrain() {}
};

#endif /* Terrain_hpp */
