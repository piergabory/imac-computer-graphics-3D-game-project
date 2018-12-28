#ifndef Entity_hpp
#define Entity_hpp

#include <memory>

#include "Object3D.hpp"
#include "ImportedMesh.hpp"

namespace GameModel {

    class Entity {
    private:

        static std::unique_ptr<GraphicsEngine::Object3D> s_entityObject;

        // todo check for use?
        const glm::vec3 position() const { return m_entityObject->position(); }

    protected:
        std::shared_ptr<GraphicsEngine::Object3D> m_entityObject;

        static GraphicsEngine::Object3D* makeObject(const char* meshPath, const char* texturePath, const char* vertexShaderProgram, const char* fragmentShaderProgram);

    public:

        inline const std::shared_ptr<GraphicsEngine::Object3D>& object() const { return m_entityObject; };

        virtual void action() {};

        virtual void onEnter() {};

        static void loadObject();

        Entity() {
            if (!s_entityObject) loadObject();
            m_entityObject =  std::make_shared<GraphicsEngine::Object3D>(*s_entityObject);
        }

        virtual ~Entity() {}
    };
}
#endif /* Entity_hpp */
