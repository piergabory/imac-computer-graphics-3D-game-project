/**
 * \file Terrain.hpp
 */
#include "Terrain.hpp"

void Terrain::testAction(Player &player) {
    m_chunks.front()->entityAt(player.position())->action();
}

void Terrain::loadChunk(Chunk *chunkToLoad) {
    m_chunks.emplace_back(chunkToLoad);
    m_chunks.back()->rotate(m_nextLoadedChunkOrientation);
    m_chunks.back()->translate(m_nextChunkPosition);
}

void Terrain::progress(const float progress){
    // creates a rotation matrix from the front's chunk orientation and creates the translation vector
    glm::vec3 translationVector = glm::vec3(glm::rotate(glm::mat4(1), m_chunks.front()->orientation(), glm::vec3(0,1,0)) * glm::vec4(0.f,0.f,progress, 1.f));
    for (std::list<std::unique_ptr<Chunk>>::iterator chunkIterator = m_chunks.begin(); chunkIterator != m_chunks.end(); ++chunkIterator) {
        (*chunkIterator)->translate(translationVector);
    }
}
