//
//  Window.cpp
//  product
//
//  Created by Pierre Gabory on 16/11/2018.
//

#include "Window.hpp"

namespace GraphicsEngine
{

    Window::Window(uint width, uint height, const char* title):
        m_pixelWidth(height), m_pixelHeight(width)
    {
        m_sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        
        if (m_sdlWindow == nullptr)
        {
            throw Exception("Failed to create SDL window", SDL_GetError());
        }
        
        m_glContext = SDL_GL_CreateContext(m_sdlWindow);
        
        reset();
    }

    void Window::resizeTo(uint width, uint height) {
        m_pixelWidth = width;
        m_pixelHeight = height;
        reset();
    }

    void Window::reset() {
        // upate
        glViewport(0, 0, m_pixelWidth, m_pixelHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
            // reset view matrix
        #ifdef __APPLE__
            GLKMatrix4 orthoMat = GLKMatrix4MakeOrtho(0.f, aspect(), 1.f, 0.f, -1.f, 1.f);
            glLoadMatrixf(orthoMat.m);
        #else
            gluOrtho2D(0.f, aspect(), 1.f, 0.f);
        #endif
    }

}
