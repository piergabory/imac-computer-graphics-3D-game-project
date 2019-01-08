#include "Chunk.hpp"

namespace GameModel {

    Entity* Chunk::entityAt(Position position) {
        switch(position) {
            case Position::LEFT: return left.get();
            case Position::MIDDLE: return middle.get();
            case Position::RIGHT: return right.get();
        }
    }



    std::set< std::shared_ptr<GraphicsEngine::Object3D> >  Chunk::objects() {
        std::set< std::shared_ptr<GraphicsEngine::Object3D> > returnedSet;
        returnedSet.insert(left->object());
        returnedSet.insert(middle->object());
        returnedSet.insert(right->object());

        return returnedSet;
    }



    void Chunk::rotate(float &angle) {
        const glm::vec3 UP(0.f,1.f,0.f);

        // get relative position of the l/r entity to the middle one
        glm::vec3 leftOffset(middle->object()->position() - left->object()->position());
        glm::vec3 rightOffset(middle->object()->position() - right->object()->position());

        // create rotation matrix out of the angle and UP vector
        glm::mat4 rotation(glm::rotate(glm::mat4(1), angle, UP));

        // translate object by their offset time the rotation.
        left->object()->translate(leftOffset + glm::vec3(rotation * glm::vec4(leftOffset, 1)));
        right->object()->translate(rightOffset + glm::vec3(rotation * glm::vec4(rightOffset, 1)));

        // spin all object on their center
        middle->object()->rotate(angle, UP);
        left->object()->rotate(angle, UP);
        right->object()->rotate(angle, UP);

        // 
        m_orientation += angle;
    }



    void Chunk::translate(glm::vec3 direction) {
        left->object()->globalTranslate(direction);
        middle->object()->globalTranslate(direction);
        right->object()->globalTranslate(direction);
    }



    Chunk::Chunk(Entity* leftEntity, Entity* middleEntity, Entity* rightEntity):
    left(leftEntity), middle(middleEntity), right(rightEntity) {
        left->object()->translate(glm::vec3(-m_ENTITY_WIDTH, 0.f, 0.f));
        middle->object()->translate(glm::vec3(0.f, 0.f, 0.f));
        right->object()->translate(glm::vec3(m_ENTITY_WIDTH, 0.f, 0.f));
    }



    Chunk::Chunk(Chunk& source) {
        left = std::move(source.left);
        middle = std::move(source.middle);
        right = std::move(source.right);
    }


}
