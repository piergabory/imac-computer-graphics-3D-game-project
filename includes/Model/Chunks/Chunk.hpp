/**
 * \file Chunk.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Chunk_hpp
#define Chunk_hpp
#pragma once

#include <set>

#include "Player.hpp"
#include "Entity.hpp"

#include "Jump.hpp"
#include "Slide.hpp"
#include "Wall.hpp"
#include "PowerUp.hpp"
#include "Coin.hpp"

namespace GameModel {

    /**
     * CHUNK CLASS
     *
     * \brief One entity length peice of the terrain. contains 3 entity reference for the left, middle and right lane of the terrain.
     * Has methods to orientate and move the elements in one single block
     * Defines where the chunk entry point and exit point is (used for turning chunk mainly)
     */
    class Chunk {
    private:
        /// \brief Entity dimentions
        /// \todo replace with dynamically determined value from the Entity class
        // static const floats can only be initialized in source file ( https://stackoverflow.com/a/2454082 )
        static const float s_ENTITY_WIDTH;
        static const float s_ENTITY_LENGTH;

        // properties
        /// \brief Entity reference pointers.
        std::unique_ptr<Entity> left;
        std::unique_ptr<Entity> middle;
        std::unique_ptr<Entity> right;

        /// \brief Chunk orientation angle, in radians
        float m_orientation = 0;

    public:

        /// \brief rotates the chunk along the Y axis
        /// Will move the left and right entity to keep sticking to the middle one
        void rotate(float &angle);

        /// \brief translates the chunk in the scene reference frame
        void translate(glm::vec3 direction);

        /// \brief observer function called when a player enters the chunk
        /// \todo check of usefulness
        virtual void onEnter() {}


        // getter

        ///\brief returns the entity the player is standing on
        Entity* entityAt(Position position);

        /// \brief orientation getter, radians value
        inline const float orientation() const { return m_orientation; }

        /// \brief returns all the entity's objects instances in a set.
        std::set< std::shared_ptr<GraphicsEngine::Object3D> > objects();

        /// \brief point coordinates of where the next chunk can connect to
        inline virtual const glm::vec3 exitPosition() const { return glm::vec3(0, 0, s_ENTITY_WIDTH);}

        /// \brief Radians angle value of the orientation of the next chunk relative to this chunk.
        inline virtual const float exitOrientation() const { return 0; }
        

        // constructors

        /// standard chunk constructor
        Chunk(Entity* leftEntity, Entity* middleEntity, Entity* rightEntity);

        /// construct a homogenous chunk
        Chunk(Entity* allEntities) : Chunk(allEntities, allEntities, allEntities) {}

        /// construct an empty chunk
        Chunk() : Chunk(new Entity(), new Entity(), new Entity()) {}

        // copy constructor
        Chunk(Chunk& source);

        // destructor
        virtual ~Chunk() {}
    };

}
#endif /* Chunk_hpp */
