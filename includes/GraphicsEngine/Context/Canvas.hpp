/**
 * \file Canvas.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Canvas_hpp
#define Canvas_hpp
#pragma once

#include "Context.hpp"
#include "Object2D.hpp"
#include "Button.hpp"
#include "Menu.hpp"

#include "Digit.hpp"
#include "Number.hpp"

namespace GraphicsEngine {

    /**
     * CANVAS CLASS
     *
     * Context Sub-class
     * \brief Contains and manages 2D objects.
     */
    class Canvas : public Context<Object2D> {
    private:

        /// lifecycle methods
        /// \brief disable Depth testing and back-face culling
        void contextWillRender() const override{
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);

            // enable blending for gradient tansparency
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //parameters for blending
        }

    public:
        ///\brief constructor
        Canvas() : Context<Object2D>() {}

        ///\brief destructor
        ~Canvas() {}
    };
}

#endif /* Canvas_hpp */
