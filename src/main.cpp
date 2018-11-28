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
#include "Material.hpp"
#include "Exceptions.hpp"

#include "CommonStructs.hpp"

int main(int argc, const char * argv[]) {
    GraphicsEngine::Controller graphicsEngineController;
    graphicsEngineController.setup();
    
    // load shaders
    GraphicsEngine::Material *material;
    try {
         material = new GraphicsEngine::Material(new GraphicsEngine::Texture("../textures/test.png"), new GraphicsEngine::PerspectiveShaderProgram("../shaders/triangle.vs.glsl", "../shaders/triangle.fs.glsl"));
    } catch(GraphicsEngine::InitialisationException error) {
        std::cerr << error.what();
    }
    
    
    graphicsEngineController.printInfos();
    
    // Hello triangle
    std::vector<GraphicsEngine::Vertex> helloTriangle;
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(-1.f,0.f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f,0.f)));
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(1.f,0.f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.5f,0.f)));
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(0.f,1.f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(0.f,1.0f)));
    
    GraphicsEngine::Object *object = new GraphicsEngine::Object(new GraphicsEngine::Mesh(helloTriangle), material);
    
    graphicsEngineController.addObjectToCurrentScene(object);
    
    
    while (true) {
        Uint32 startTime = SDL_GetTicks();

        graphicsEngineController.draw();
        graphicsEngineController.pollEvents();
        
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < 50) {
            SDL_Delay(50 - elapsedTime);
        }
    }
    
    
    delete object;
    delete material;
    
    return 0;
}
