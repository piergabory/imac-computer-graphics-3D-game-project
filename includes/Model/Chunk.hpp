
#ifndef Chunk_hpp
#define Chunk_hpp

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

#endif /* Chunk_hpp */
