//
//  ImageData.cpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//

#include "ImageData.hpp"

namespace GraphicsEngine {
    ImageData::ImageData(const char* fileName) :
    m_sdlImagePtr(IMG_Load(fileName))
    {
        if(m_sdlImagePtr == nullptr) throw InitialisationException("Failed to load image file: ", fileName);
    }
    
    ImageData::~ImageData() {
        SDL_FreeSurface(m_sdlImagePtr);
    }
}
