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
    std::vector<GraphicsEngine::Vertex> verticies;
    
    // Hello triangle
    verticies.push_back(GraphicsEngine::Vertex(glm::vec3(-1.f,0.f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f,0.f)));
    verticies.push_back(GraphicsEngine::Vertex(glm::vec3(1.f,0.f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.f,0.f)));
    verticies.push_back(GraphicsEngine::Vertex(glm::vec3(0.f,1.f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(0.f,0.f)));
    
    GraphicsEngine::setup();
    GraphicsEngine::Object object(verticies);
    
    try {
        GraphicsEngine::ShaderProgram shaderProgram("../shaders/triangle.fs.glsl", "../shaders/triangle.fs.glsl");
        shaderProgram.use();
    } catch(GraphicsEngine::Exception error) {
        std::cerr << error.what();
    }
    
    
    
    while (true)
    {
        Uint32 startTime = SDL_GetTicks();
        
        GraphicsEngine::draw();
        
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < 50)
        {
            SDL_Delay(50 - elapsedTime);
        }
    }
    
    return 0;
}
