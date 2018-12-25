#include "SaveLoader.hpp"

SaveLoader* SaveLoader::s_singletonInstance = nullptr;

SaveLoader* SaveLoader::instance() {
    if (!s_singletonInstance) {
        s_singletonInstance = new SaveLoader();
    }
    return s_singletonInstance;
}


void SaveLoader::openFile(LocalFilePath jsonFilePath) {
    std::ifstream saveFileStream(jsonFilePath, std::ifstream::binary);
    if (saveFileStream.fail() || saveFileStream.bad() || saveFileStream.eof()) throw std::ios_base::failure("Couldn't open save file at:" + jsonFilePath);
    saveFileStream >> m_jsonBuffer;
}

GameModel::Entity* SaveLoader::readEntity(uint identifier, uint index) {
    switch ((EntityTypes) identifier) {
        case EntityTypes::EMPTY :
            return new GameModel::Entity();

        default:
            std::string info = "Unkown entity id:" + std::to_string(identifier) + " at index: " + std::to_string(index);
            throw SaveLoaderException("Corrupted save file.", info.c_str());
    }
}

void SaveLoader::loadChunkBuffer() {
    const Json::Value terrainArray = m_jsonBuffer["terrain"];
    if (terrainArray == Json::nullValue)
        throw SaveLoaderException("Corrupted save file.", "Couldn't read terrain array.");

    const Json::Value chunkSize = m_jsonBuffer["chunkSize"];
    if (chunkSize == Json::nullValue)
        throw SaveLoaderException("Corrupted save file.", "Couldn't read terrain array.");

    for (int index = 0; index < terrainArray.size(); index += chunkSize.asInt()) {
        GameModel::Entity* left = readEntity(terrainArray[index + 0].asUInt(), index + 0);
        GameModel::Entity* middle = readEntity(terrainArray[index + 1].asUInt(), index + 1);
        GameModel::Entity* right = readEntity(terrainArray[index + 2].asUInt(), index + 2);
        m_chunkbuffer.emplace(left,middle,right);
    }
}
