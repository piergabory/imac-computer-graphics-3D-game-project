//
//  Canvas.hpp
//  xcode target
//
//  Created by Pierre Gabory on 17/12/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include "Context.hpp"
#include "Object2D.hpp"

namespace GraphicsEngine {
    class Canvas : public Context<Object2D> {
    private:
        void contextWillRender() {
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }

    public:
        Canvas() : Context<Object2D>() {}
        ~Canvas() {}
    };
}

#endif /* Canvas_hpp */
