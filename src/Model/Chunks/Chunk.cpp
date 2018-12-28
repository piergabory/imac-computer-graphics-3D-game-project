#include "Chunk.hpp"

namespace GameModel {

    const float Chunk::s_ENTITY_WIDTH = 2;
    const float Chunk::s_ENTITY_LENGTH = 2;

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
        glm::vec3 up(0.f,1.f,0.f);
        glm::vec3 leftOffset(middle->object()->position() - left->object()->position());
        glm::vec3 rightOffset(middle->object()->position() - right->object()->position());

        glm::mat4 rotation(glm::rotate(glm::mat4(1), angle, up));

        left->object()->translate(leftOffset + glm::vec3(rotation * glm::vec4(leftOffset, 1)));
        right->object()->translate(rightOffset + glm::vec3(rotation * glm::vec4(rightOffset, 1)));

        middle->object()->rotate(angle, up);
        left->object()->rotate(angle, up);
        right->object()->rotate(angle, up);

        m_orientation += angle;
    }

    void Chunk::translate(glm::vec3 direction) {
        left->object()->globalTranslate(direction);
        middle->object()->globalTranslate(direction);
        right->object()->globalTranslate(direction);
    }

    Chunk::Chunk(Entity* leftEntity, Entity* middleEntity, Entity* rightEntity):
    left(leftEntity), middle(middleEntity), right(rightEntity) {
        left->object()->translate(glm::vec3(-s_ENTITY_WIDTH, 0.f, 0.f));
        middle->object()->translate(glm::vec3(0.f, 0.f, 0.f));
        right->object()->translate(glm::vec3(s_ENTITY_WIDTH, 0.f, 0.f));
    }

    Chunk::Chunk(Chunk& source) {
        left = std::move(source.left);
        middle = std::move(source.middle);
        right = std::move(source.right);
    }
}
