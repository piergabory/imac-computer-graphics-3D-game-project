//
//  ImageData.hpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//

#ifndef ImageData_hpp
#define ImageData_hpp

#include "Frameworks.hpp"
#include "Exceptions.hpp"

namespace GraphicsEngine {
    class ImageData {
    private:
        SDL_Surface* m_sdlImagePtr;
    
    public:
        inline const GLuint width() const { return m_sdlImagePtr->w; }
        inline const GLuint height() const { return m_sdlImagePtr->h; }
        inline void* pixels() const { return m_sdlImagePtr->pixels; }
        
        ImageData(const char* fileName);
        ~ImageData();
    };
}

#endif /* ImageData_hpp */
