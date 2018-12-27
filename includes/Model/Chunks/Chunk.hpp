
#ifndef Chunk_hpp
#define Chunk_hpp

#include "Turn.hpp"
#include "Player.hpp"


class Chunk {
private:
    // static const floats can only be initialized in source file (https://stackoverflow.com/a/2454082)
    static const float s_ENTITY_WIDTH;

    // properties
    std::unique_ptr<Entity> left;
    std::unique_ptr<Entity> middle;
    std::unique_ptr<Entity> right;

    float m_orientation = 0;

public:
    inline const float orientation() const { return m_orientation; }

    void rotate(float &angle);
    void translate(glm::vec3 direction);

    // getter
    Entity* entityAt(Position position);

    // constructor
    Chunk(Entity* leftEntity, Entity* middleEntity, Entity* rightEntity);

    // copy constructor
    Chunk(Chunk& source);

    // destructor
    ~Chunk() {}
};

#endif /* Chunk_hpp */
