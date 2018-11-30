/**
 * ImageData.cpp
 */

#include "ImageData.hpp"

namespace GraphicsEngine {
    
    // constructor
    ImageData::ImageData(const char* fileName) :
    m_sdlImagePtr(IMG_Load(fileName)) {
        // check if the image loaded successfully
        if(m_sdlImagePtr == nullptr) throw InitialisationException("Failed to load image file: ", fileName);
    }
    
    // destructor
    ImageData::~ImageData() {
        // liberate memory of the SDL image pixels
        SDL_FreeSurface(m_sdlImagePtr);
    }
}
