/**
 * FRAMEWORK.H
 * ------------------
 * Handles the loading of the right librairies on different OS
 * This file extracted from last year project.
 */

#ifndef frameworks_h
#define frameworks_h

// Mac OS
#if defined(MacOS) || defined(__APPLE__)
    #include <SDL2/SDL.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    // Apple has deprecated gluOrtho2D for their OpenGL Support
    #include <GLKit/GLKMatrix4.h>
    #define SET_ORTHO_MATRIX(left, right, bottom, top)  { \
            GLKMatrix4 orthoMat = GLKMatrix4MakeOrtho(left, right, bottom, top, -1.0f, 1.0f); \
            glLoadMatrixf(orthoMat.m); \
    } \

// Linux
#else
    #include <SDL2/SDL.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    #define SET_ORTHO_MATRIX(left, right, bottom, top) {gluOrtho2D(left,right,bottom,top);}
#endif

#endif /* frameworks_h */
