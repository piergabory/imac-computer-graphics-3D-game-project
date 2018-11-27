//
//  main.cpp
//  Projet_S2_CG_CPP
//
//  Created by Pierre Gabory on 17/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#include <exception>
#include <iostream>

#include "GraphicsEngine.hpp"
#include "ShaderProgram.hpp"
#include "Exceptions.hpp"

int main(int argc, const char * argv[]) {
    GraphicsEngine::Controller graphicsEngineController;
    
    std::vector<GraphicsEngine::Vertex> vertices;
    
    // Hello triangle
    vertices.push_back(GraphicsEngine::Vertex(glm::vec3(-1.f,0.f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f,0.f)));
    vertices.push_back(GraphicsEngine::Vertex(glm::vec3(1.f,0.f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.f,0.f)));
    vertices.push_back(GraphicsEngine::Vertex(glm::vec3(0.f,1.f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(0.f,0.f)));
    
    graphicsEngineController.setup();
    
    try {
        GraphicsEngine::ShaderProgram shaderProgram("../shaders/triangle.vs.glsl", "../shaders/triangle.fs.glsl");
        shaderProgram.use();
    } catch(GraphicsEngine::InitialisationException error) {
        std::cerr << error.what();
    }
    
    graphicsEngineController.addObjectToCurrentScene(new GraphicsEngine::Object(vertices));
    
    graphicsEngineController.printInfos();
    
    
    
    
    
    
    
    
    
    

    
    
    // VERTEX BUFFER OBJECT -------------------------------------------------------
    
    // define vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    
    // bind vbo to a target
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    // define hello triangle vertices:
    GLfloat test_vertices[] = {
        -0.2f, -0.2f,  0.f, 1.f, 0.f, 0.f, //red
        0.8f, -0.2f,  0.f, 0.f, 1.f, 0.f, //green
        0.3f, 0.8f,  0.f, 0.f, 0.f, 1.f //blue
    };
    
    // push vertices to the vbo target
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), test_vertices, GL_STATIC_DRAW);
    
    // release the vbo from the target (to avoid accidental changes)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    
    // VERTEX ARRAY OBJECT -------------------------------------------------------
    
    // define
    GLuint vao;
    glGenVertexArrays(1, &vao);
    
    // bind
    glBindVertexArray(vao);
    
    // activate vertex attributes
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;
    
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    
    // set attributes to the vertex array
    // select which vbo were using (we only have one tho)
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    /**
     * 1. Index of the type of the attribute
     * 2. number of values for that attribute (2 because were in 2d right now)
     * 3. Toogle normalisation
     * 4. number of bites to the next attribute values.
     * 5. array offset start.
     */
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void*) (0 * sizeof(GLfloat)));
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void*) (3 * sizeof(GLfloat)));
    
    // release
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    
    
    
    
    
    
    while (true) {
        Uint32 startTime = SDL_GetTicks();
        
        
        
        
        
        
        // janitor cleans the room
        glClear(GL_COLOR_BUFFER_BIT);
        
        // draw the vertex array, type of vertex, index of the first and number of vertex to draw.
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        
        
        graphicsEngineController.draw();
        
        SDL_PumpEvents();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < 50) {
            SDL_Delay(50 - elapsedTime);
        }
    }
    
    return 0;
}
