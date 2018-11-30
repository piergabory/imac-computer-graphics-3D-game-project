/**
 * Frameworks.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Frameworks_hpp
#define Frameworks_hpp


/**
 * Includes for different operating systems
 */

// Mac OS includes
// ------------------------------------------------
// disable MacOS Mojave OpenGL deprecation warnings
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__

    // SDL library and extensions
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>

    // GLEW
    #include <GL/glew.h>

    // OpenGL
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>


// Linux includes
// ------------------------------------------------
#else

    // SDL library and extensions
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>

    // GLEW
    #include <GL/glew.h>

    // OpenGL
    #include <GL/gl.h>
    #include <GL/glu.h>

#endif

#endif // end: Frameworks_hpp
