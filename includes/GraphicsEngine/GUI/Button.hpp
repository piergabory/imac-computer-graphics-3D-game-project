//
//  Button.hpp
//  xcode target
//
//  Created by Pierre Gabory on 18/12/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <functional>

#include "Object2D.hpp"
#include "EventManager.hpp"

namespace GraphicsEngine {

    class Button : public Object2D, Events::MouseEventObserver {
    private:
        std::function<void(Button*, unsigned char)> m_onClickCallback;

        const glm::vec2 m_boundingBoxTopLeftCorner;
        const glm::vec2 m_boundingBoxBottomRightCorner;

        void mouseReleaseHandler(unsigned char button) override;

        bool checkBounds() const;

        static glm::ivec2 s_windowPixelSize;

    public:
        static void initializeButtons(const glm::ivec2 &windowPixelSize);

        Button(const glm::vec2 &position, const glm::vec2 &size, const LocalFilePath image, const std::function<void(Button*, unsigned char)> &callback);


        Button(const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<Texture> sprite, const std::function<void(Button*, unsigned char)> &callback);

        Button(const Button &copy) = default;
    };
}


#endif /* Button_hpp */
