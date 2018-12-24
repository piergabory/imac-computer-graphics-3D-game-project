#ifndef SaveLoader_hpp
#define SaveLoader_hpp

#include <queue>

#include "CommonStructs.hpp"
#include "Chunk.hpp"

class SaveLoader {

private:

    std::queue<GameModel::Chunk> m_chunkbuffer;

    void loadFromFile(LocalFilePath file) {

    }

    static SaveLoader* s_singletonInstance;

    SaveLoader() {};

public:

    static SaveLoader* instance();

    ~SaveLoader() {};
};

#endif /* SaveLoader_hpp */
