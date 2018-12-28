/**
 * \file Terrain.hpp
 *
 * IMAC 2 Project CG CPP
 */

#ifndef Terrain_hpp
#define Terrain_hpp

#include <deque>

#include "Chunk.hpp"
#include "TurningChunk.hpp"

namespace GameModel {

    /// \brief Cadinal Direction enumeration
    /// to represent chunk orientation
    enum class CardinalDirections : int {
        NORTH = 0,
        EAST = 90,
        SOUTH = 180,
        WEST = -90
    };


    /**
     * TERRAIN CLASS
     *
     * \brief Aggregates chunks.
     * Points the active chunk.
     */
    class Terrain {
    private:

        /// \brief Number of chunks behind the player
        /// Chunk count still around after being visited by the player.
        const uint m_CHUNK_COUNT_AFTER_PLAYER = 5;

        /// \brief Chunk container
        /// Dequeue allows random access (to get active chunk) and quick front/back edits
        std::deque< std::unique_ptr<Chunk> > m_chunks;

        /// \brief Angle in randians of the next chunk to be added at the end of the terrain.
        float m_nextLoadedChunkOrientation = 0;

        /// \brief Position of the next chunk to be added
        glm::vec3 m_nextLoadedChunkPosition = glm::vec3(0.f,0.f,0.f);


        /// \brief active chunk getter.
        inline const std::unique_ptr<Chunk>& activeChunk() const { return m_chunks[m_CHUNK_COUNT_AFTER_PLAYER]; }
        inline std::unique_ptr<Chunk>& activeChunk() { return m_chunks[m_CHUNK_COUNT_AFTER_PLAYER]; }


    public:
        /// \brief destroys old chunks and shifts to the next one.
        inline void nextChunk() {
            m_chunks.pop_front();
            activeChunk()->onEnter();
        }

        /// \brief orientation getter
        /// Converts radian degree to Cardinal direction
        const CardinalDirections facing() const;

        /// \brief test player when entering the chunk.
        void enterChunk(Player &player);

        /// \brief test player on current chunk.
        void testAction(Player &player);

        /// \brief push new chunks in the container
        /// Places the objects in the scene.
        void loadChunk(Chunk *chunkToLoad);

        /// \brief displaces all objects in the scene in the direction of the active chunk.
        /// Creates the illusion of movement under the player.
        void progress(const float progress);


        // constructor
        Terrain() {}

        // destructor
        ~Terrain() {}
    };

}

#endif /* Terrain_hpp */
