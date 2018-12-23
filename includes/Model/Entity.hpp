#ifndef Entity_hpp
#define Entity_hpp

#include <memory>

#include "Object3D.hpp"

class Entity {
private:
    std::shared_ptr<GraphicsEngine::Object3D> m_entityObject;
    const glm::vec3 position() const { return m_entityObject->position(); }

public:
    virtual void action() {};

    Entity(std::shared_ptr<GraphicsEngine::Object3D> entityObject):
        m_entityObject(entityObject)
    {}

    virtual ~Entity() {}
};

#endif /* Entity_hpp */
