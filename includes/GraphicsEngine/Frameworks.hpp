#ifndef Frameworks_hpp
#define Frameworks_hpp

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
    // Mac OS
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <GL/glew.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>


//    #define glGenVertexArrays glGenVertexArraysAPPLE
//    #define glBindVertexArray glBindVertexArrayAPPLE
//    #define glDeleteVertexArrays glDeleteVertexArraysAPPLE

#else
    // Linux
    #include <GL/glew.h>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <GL/gl.h>
    #include <GL/glu.h>

#endif

#endif
