/**
 * ImageData.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef ImageData_hpp
#define ImageData_hpp

#include "Frameworks.hpp"
#include "Exceptions.hpp"

/**
 * IMAGE DATA CLASS
 *
 * Facade for SDL images (IMG_LOAD), with access to image data and attributes
 */
namespace GraphicsEngine {
    class ImageData {
    private:
        // pointer to the pixel data loaded by sdl
        SDL_Surface* m_sdlImagePtr;
    
    public:
        // getters
        inline const GLuint width() const { return m_sdlImagePtr->w; }
        inline const GLuint height() const { return m_sdlImagePtr->h; }
        
        inline void* pixels() { return m_sdlImagePtr->pixels; }
        inline const void* pixels() const { return m_sdlImagePtr->pixels; }
        
        // constructor
        // takes the path of the image as a cstring
        ImageData(const char* fileName);
        
        // destructor
        ~ImageData();
    };
}

#endif /* ImageData_hpp */
