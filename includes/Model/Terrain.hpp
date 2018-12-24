/**
 * \file Terrain.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Terrain_hpp
#define Terrain_hpp

#include <list>
#include <memory>

#include "Entity.hpp"
#include "Player.hpp"


struct Chunk {
    // properties
    std::unique_ptr<Entity> left;
    std::unique_ptr<Entity> middle;
    std::unique_ptr<Entity> right;

    // getter
    Entity* entityAt(Position position) {
        switch(position) {
            case Position::LEFT: return left.get();
            case Position::MIDDLE: return middle.get();
            case Position::RIGHT: return right.get();
        }
    }

    // constructor
    Chunk(Entity* leftEntity, Entity* middleEntity, Entity* rightEntity):
    left(leftEntity), middle(middleEntity), right(rightEntity)
    {}

    // copy constructor
    Chunk(Chunk& source) {
        left = std::move(source.left);
        middle = std::move(source.middle);
        right = std::move(source.right);
    }

    // default constructor
    Chunk() {}

    // destructor
    ~Chunk() {}
};


class Terrain {
private:
    std::list<Chunk> m_chunks;

public:
    inline void nextChunk() { m_chunks.pop_front(); }

    void testAction(Player &player);

    void loadChunk(Entity* left, Entity* middle, Entity* right);

    void progress(const float progress);

    std::set< std::shared_ptr<Entity> > loadEntity3DObjects();

    Terrain() {}
    ~Terrain() {}
};


#endif /* Terrain_hpp */
