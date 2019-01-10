/**
 * \file TurningChunk.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef TurningChunk_hpp
#define TurningChunk_hpp
#pragma once

#include "Chunk.hpp"
#include "Turn.hpp"

namespace GameModel {

    /**
     *  TURNING CHUNK CLASS
     *
     * \brief Specialzed chunk for terrain rotations
     * Handles animation of objects at rotation points
     *  Chunk Subclass
     */

    class TurningChunk : public Chunk {
        /// \brief direction of the turning chunk (LEFT, RIGHT)
        const TurnDirection m_direction;

        const float m_ENTITY_WIDTH = 2;
        const float m_ENTITY_LENGTH = 6;

    public:
        // getters
        /// \brief point coordinates of where the next chunk can connect to
        inline virtual const glm::vec3 exitPosition() const {
            switch(m_direction) {
                case TurnDirection::LEFT: return glm::vec3(-m_ENTITY_LENGTH/m_ENTITY_WIDTH,0,m_ENTITY_LENGTH/m_ENTITY_WIDTH);
                case TurnDirection::RIGHT: return glm::vec3(m_ENTITY_LENGTH/m_ENTITY_WIDTH,0,m_ENTITY_LENGTH/m_ENTITY_WIDTH);
            }
            return glm::vec3(0,0,0); //remoove warning
        }


        /// \brief Radians angle value of the orientation of the next chunk relative to this chunk.
        inline virtual const float exitOrientation() const { return glm::radians((float)m_direction); }


        /// \brief observer function called when a player enters the chunk
        /// \todo check of usefulness
        inline virtual void onEnter() {  }

        
        // constructor
        TurningChunk(TurnDirection direction, std::shared_ptr<GraphicsEngine::Animatable> cameraAnimatable, std::shared_ptr<GraphicsEngine::Animatable> playerAnimatable):
        Chunk(new Turn(direction, cameraAnimatable, playerAnimatable), new Turn(direction, cameraAnimatable, playerAnimatable), new Turn(direction, cameraAnimatable, playerAnimatable)),
        m_direction(direction)
        {}

        // copy constructor
        TurningChunk(TurningChunk& source): Chunk(source), m_direction(source.m_direction) {}

        ~TurningChunk() {}
    };
}
#endif /* TurningChunk_hpp */
