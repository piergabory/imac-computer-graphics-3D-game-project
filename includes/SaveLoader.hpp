#ifndef SaveLoader_hpp
#define SaveLoader_hpp

#include <queue>
#include <fstream>
#include <string>

#include <json/json.h>

#include "Exceptions.hpp"
#include "CommonStructs.hpp"
#include "Chunk.hpp"

enum class EntityTypes : uint {
    EMPTY = 0, TURN, JUMP, CROUCH, COIN
};

class SaveLoader {

private:

    Json::Value m_jsonBuffer;

    std::queue<GameModel::Chunk> m_chunkbuffer;

    GameModel::Entity* readEntity(uint identifier, uint index);

    static SaveLoader* s_singletonInstance;

    SaveLoader() {};

public:

    void openFile(LocalFilePath jsonFilePath);

    inline std::queue<GameModel::Chunk>& chunks() { return m_chunkbuffer; }

    void loadChunkBuffer();

    static SaveLoader* instance();

    ~SaveLoader() {};
};

#endif /* SaveLoader_hpp */
