/**
 * \file Entity.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Entity_hpp
#define Entity_hpp

#include <memory>

#include "Object3D.hpp"
#include "ImportedMesh.hpp"

namespace GameModel {

    /**
     * ENTITY CLASS
     *
     * \brief virtual super-class representing an empty bit of terrain
     * Its subclass can represent coins, bonuses, turns or different obstacles
     * \warning Entities cannot be called before initialization of the graphic engine
     */
    class Entity {
    private:
        /// \brief static default entity object.
        /// use this instance to clone new objects
        static std::unique_ptr<GraphicsEngine::Object3D> s_entityObject;


    protected:
        /// \brief 3D object instance of the entity.
        /// When this pointer is forgotten (at entity destruction) the object should be removed from the viewport and destroyed
        std::shared_ptr<GraphicsEngine::Object3D> m_entityObject;


        /// \brief static object factory method
        static GraphicsEngine::Object3D* makeObject(const char* meshPath, const char* texturePath, const char* vertexShaderProgram, const char* fragmentShaderProgram);



    public:
        /// \brief object instance getter
        inline const std::shared_ptr<GraphicsEngine::Object3D>& object() const { return m_entityObject; };


        /// \brief repeated tests on the player on each frame
        virtual void action() {};


        /// \brief one-time tests on the player on first visit
        virtual void onEnter() {};


        /// \brief object factory caller with parameters for an empty object
        /// automagically called on first instanciation of Entity
        static void loadObject();


        /// \brief constructor
        /// \warning cannot be called before graphics engine initialisation
        Entity();

        // destructor
        virtual ~Entity() {}
    };

}

#endif /* Entity_hpp */
