/**
 * \file Terrain.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Terrain_hpp
#define Terrain_hpp

#include <list>

#include "Chunk.hpp"
namespace GameModel {
    class Terrain {
    private:
        std::list<Chunk> m_chunks;

    public:
        inline void nextChunk() { m_chunks.pop_front(); }

        void testAction(Player &player);

        void loadChunk(Entity* left, Entity* middle, Entity* right, float offset = 0);

        void progress(const float progress);

        std::set< std::shared_ptr<Entity> > loadEntity3DObjects();

        Terrain() {}
        ~Terrain() {}
    };
}

#endif /* Terrain_hpp */
