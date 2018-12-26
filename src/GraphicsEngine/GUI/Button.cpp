/**
 * \file Button.cpp
 */

#include "Button.hpp"

namespace GraphicsEngine {

    // redefine static member
    glm::ivec2 Button::s_windowPixelSize;



    bool Button::checkBounds() const {
        // compute mouse position from pixels to float vector
        int pixelMousePositionX, pixelMousePositionY;
        SDL_GetMouseState(&pixelMousePositionX, &pixelMousePositionY);
        glm::vec2 mousePosition(pixelMousePositionX * 2.f / s_windowPixelSize.x - 1.f, 1.f -  pixelMousePositionY * 2.f / s_windowPixelSize.y);

        // check bounds
        return mousePosition.x > m_boundingBoxTopLeftCorner.x
            && mousePosition.x < m_boundingBoxBottomRightCorner.y
            && mousePosition.y > m_boundingBoxTopLeftCorner.x
            && mousePosition.y < m_boundingBoxBottomRightCorner.y;
    }



    void Button::mouseReleaseHandler(const unsigned char button) {
        // if in bounds, calls the callback
        if (checkBounds()) m_onClickCallback(this, button);
    }



    Button::Button(const glm::vec2 &position, const glm::vec2 &size, const LocalFilePath image, const std::function<void(Button*, const unsigned char)> &callback):
        // superclass constructor
        Object2D(position, size, image),

        // callback
        m_onClickCallback(callback),

        // keep bounds
        m_boundingBoxTopLeftCorner(position),
        m_boundingBoxBottomRightCorner(position + size)

    {
        // check if the static property was set
        assert(s_windowPixelSize != glm::ivec2());

        // folows mouse events
        Events::Manager::instance()->subscribe(this);
    }


    // Same constructor, using textures instead of image paths.
    Button::Button(const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<Texture> sprite, const std::function<void(Button*, const unsigned char)> &callback):
        Object2D(position, size, sprite),
        m_onClickCallback(callback),
        m_boundingBoxTopLeftCorner(position),
        m_boundingBoxBottomRightCorner(position + size)
    {
        // check if the static property was set
        assert(s_windowPixelSize != glm::ivec2());

        Events::Manager::instance()->subscribe(this);
    }

    // static setter
    void Button::initializeButtons(const glm::ivec2 &windowPixelSize) {
        s_windowPixelSize = windowPixelSize;
    }
}
