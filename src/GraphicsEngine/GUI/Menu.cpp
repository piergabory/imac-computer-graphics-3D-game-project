/**
 * \file Menu.cpp
 */

#include "Menu.hpp"

namespace GraphicsEngine {
    Menu::Menu(std::shared_ptr<Texture> texture) : Object2D(glm::vec2(-1,1), glm::vec2(2,-2), texture){};
    
    Menu::~Menu(){};
}
