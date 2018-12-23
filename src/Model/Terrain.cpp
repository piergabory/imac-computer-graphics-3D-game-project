/**
 * \file Terrain.hpp
 */
#include "Terrain.hpp"

void Terrain::testAction(Player &player) {
    (m_chunks.front())[player.position()]->action(/*player*/);
}

void Terrain::loadChunk(Entity* left, Entity* middle, Entity* right) {
    std::map<Position, std::unique_ptr<Entity> > chunk;
    chunk[Position::LEFT] = std::unique_ptr<Entity>(left);
    chunk[Position::MIDDLE] = std::unique_ptr<Entity>(middle);
    chunk[Position::RIGHT] = std::unique_ptr<Entity>(right);
    m_chunks.push(chunk);
}
