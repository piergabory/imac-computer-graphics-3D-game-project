//
//  Window.hpp
//  product
//
//  Created by Pierre Gabory on 16/11/2018.
//

#ifndef Window_hpp
#define Window_hpp

#include "Frameworks.hpp"
#include "Exceptions.hpp"

namespace GraphicsEngine
{

    class Window
    {
        
    private:
        
        SDL_Window* m_sdlWindow;
        
        SDL_GLContext m_glContext;
        
        uint m_pixelWidth;
        
        uint m_pixelHeight;
        
        void reset();
        
    public:
        Window(uint width = 800, uint height = 600, const char* = "");
        
        ~Window() {};
        
        void resizeTo(uint width, uint height);
        
        
        // Getters
        inline const uint width() const { return m_pixelWidth; }
        
        inline const uint height() const { return m_pixelHeight; }
        
        inline const float aspect() const { return m_pixelWidth / (float)m_pixelHeight; }
    };

}

#endif /* Window_hpp */
