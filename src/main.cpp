//
//  main.cpp
//  Projet_S2_CG_CPP
//
//  Created by Pierre Gabory on 17/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#include <exception>
#include <iostream>

#include "EventObservers.hpp"
#include "GraphicsEngine.hpp"
#include "Material.hpp"
#include "Exceptions.hpp"

#include "CommonStructs.hpp"


struct testQuit : QuitEventObserver {
    bool status;
    
    testQuit() { status = true; }
    
    void quitEventHandler() override {
        status = false;
        GraphicsEngine::Controller::instance()->close();
    }
};

int main(int argc, const char * argv[]) {
    GraphicsEngine::Controller::instance()->setup();
    
    
    
    // load shaders
    GraphicsEngine::Material *material;
    try {
         material = new GraphicsEngine::Material(new GraphicsEngine::Texture("../textures/test.png"), new GraphicsEngine::PerspectiveShaderProgram("../shaders/triangle.vs.glsl", "../shaders/triangle.fs.glsl"));
    } catch(GraphicsEngine::InitialisationException error) {
        std::cerr << error.what();
    }
    
    
    GraphicsEngine::Controller::instance()->printInfos();
    
    // Hello triangle
    std::vector<GraphicsEngine::Vertex> helloTriangle;
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(-1.f,0.f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f,0.f)));
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(1.f,0.f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.5f,0.f)));
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(0.f,1.f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(0.f,1.0f)));
    
    GraphicsEngine::Object *object = new GraphicsEngine::Object(new GraphicsEngine::Mesh(helloTriangle), material);
    
    GraphicsEngine::Controller::instance()->activeScene()->add(object);
    
    testQuit shouldKeepRunning;
    GraphicsEngine::EventManager::instance()->subscribe(&shouldKeepRunning);
    
    while (shouldKeepRunning.status) {
        Uint32 startTime = SDL_GetTicks();

        GraphicsEngine::Controller::instance()->render();
        GraphicsEngine::Controller::instance()->pollEvents();
        
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < 50) {
            SDL_Delay(50 - elapsedTime);
        }
    }
    
    
    delete object;
    delete material;
    
    return 0;
}
