/**
 * \file Terrain.hpp
 */
#include "Terrain.hpp"

void Terrain::testAction(Player &player) {
    m_chunks.front().entityAt(player.position())->action();
}

void Terrain::loadChunk(Entity* left, Entity* middle, Entity* right, float offset) {
    left->object()->translate(glm::vec3(-2.0f,0.f,offset));
    middle->object()->translate(glm::vec3(0.f,0.f,offset));
    right->object()->translate(glm::vec3(2.0f,0.f,offset));
    m_chunks.emplace_back(left, middle, right);
}

void Terrain::progress(const float progress){
    for (std::list<Chunk>::iterator chunkIterator = m_chunks.begin(); chunkIterator != m_chunks.end(); ++chunkIterator) {
        chunkIterator->left->object()->translate(glm::vec3(0.f,0.f,progress));
        chunkIterator->middle->object()->translate(glm::vec3(0.f,0.f,progress));
        chunkIterator->right->object()->translate(glm::vec3(0.f,0.f,progress));
    }
}
