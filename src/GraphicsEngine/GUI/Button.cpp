//
//  Button.cpp
//  xcode target
//
//  Created by Pierre Gabory on 18/12/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#include "Button.hpp"

namespace GraphicsEngine {

    glm::ivec2 Button::s_windowPixelSize;

    bool Button::checkBounds() const {
        // get mouse position
        int pixelMousePositionX, pixelMousePositionY;
        SDL_GetMouseState(&pixelMousePositionX, &pixelMousePositionY);
        glm::vec2 mousePosition(pixelMousePositionX * 2.f / s_windowPixelSize.x - 1.f, 1.f -  pixelMousePositionY * 2.f / s_windowPixelSize.y);

        // check bounds
        return mousePosition.x > m_boundingBoxTopLeftCorner.x
            && mousePosition.x < m_boundingBoxBottomRightCorner.y
            && mousePosition.y > m_boundingBoxTopLeftCorner.x
            && mousePosition.y < m_boundingBoxBottomRightCorner.y;
    }

    void Button::mouseReleaseHandler(unsigned char button) {
        if (checkBounds()) m_onClickCallback(this, button);
    }

    Button::Button(const glm::vec2 &position, const glm::vec2 &size, const LocalFilePath image, const std::function<void(Button*, unsigned char)> &callback):
    Object2D(position, size, image),
    m_onClickCallback(callback),
    m_boundingBoxTopLeftCorner(position),
    m_boundingBoxBottomRightCorner(position + size) {
        // check if the static property was set
        assert(s_windowPixelSize != glm::ivec2());

        Events::Manager::instance()->subscribe(this);
    }

    Button::Button(const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<Texture> sprite, const std::function<void(Button*, unsigned char)> &callback):
    Object2D(position, size, sprite),
    m_onClickCallback(callback),
    m_boundingBoxTopLeftCorner(position),
    m_boundingBoxBottomRightCorner(position + size) {
        // check if the static property was set
        assert(s_windowPixelSize != glm::ivec2());

        Events::Manager::instance()->subscribe(this);
    }

    void Button::initializeButtons(const glm::ivec2 &windowPixelSize) {
        s_windowPixelSize = windowPixelSize;
    }
}
