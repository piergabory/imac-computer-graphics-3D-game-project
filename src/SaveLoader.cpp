#include "SaveLoader.hpp"

SaveLoader* SaveLoader::s_singletonInstance = nullptr;

SaveLoader* SaveLoader::instance() {
    if (s_singletonInstance) {
        s_singletonInstance = new SaveLoader();
    }
    return s_singletonInstance;
}
