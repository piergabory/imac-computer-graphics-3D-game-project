#ifndef Canvas_hpp
#define Canvas_hpp

#include "Context.hpp"
#include "Object2D.hpp"
#include "Button.hpp"

namespace GraphicsEngine {
    class Canvas : public Context<Object2D> {
    private:

        void contextWillRender() const override{
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }

    public:
        Canvas() : Context<Object2D>() {}
        ~Canvas() {}
        
    };
}

#endif /* Canvas_hpp */
