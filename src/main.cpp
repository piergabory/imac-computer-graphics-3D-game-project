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


struct testKeyboard : KeyboardEventObserver {
    GraphicsEngine::Camera* cameraToMove;

    void keyRealeaseHandler(unsigned char keycode) override {

        std::cout << "Key Released : " << (int)keycode << std::endl;
    };

    void keyDownHandler(unsigned char keycode) override {

        switch(keycode) {
            case 122: case 82:
                std::cout << "UP : " << (int)keycode << std::endl;
                cameraToMove->translate(glm::vec3(0.1,0,0));
                break;

            case 115: case 81:
                std::cout << "DOWN : " << (int)keycode << std::endl;
                cameraToMove->translate(glm::vec3(-0.1,0,0));
                break;

            case 113: case 80:
                std::cout << "LEFT : " << (int)keycode << std::endl;
                cameraToMove->rotate(glm::vec3(0,0,1), 6.f);
                break;

            case 100: case 79:
                std::cout << "RIGHT : " << (int)keycode << std::endl;
                cameraToMove->rotate(glm::vec3(0,0,1), -6.f);
                break;

            default:
                std::cout << "Key Pressed : " << (int)keycode << std::endl;
                break;
        }
    };
};


int main(int argc, const char * argv[]) {
    GraphicsEngine::LocalFilePath::setLocation(*argv);
    std::cout << GraphicsEngine::LocalFilePath("../does/this/look/normal?") << std::endl;

    std::cout << "GEC Setup" << std::endl;
    GraphicsEngine::Controller::instance()->setup();

    GraphicsEngine::Camera camera;
   // camera.rotate(glm::vec3(0,0,1),30);

    GraphicsEngine::Scene *scene = new GraphicsEngine::Scene(&camera);

    GraphicsEngine::Controller::instance()->loadScene(scene);



    std::cout << "Done\nGEC Materials" << std::endl;
    // load shaders
    GraphicsEngine::Material *material;
    GraphicsEngine::Texture *tex;
    GraphicsEngine::PerspectiveShaderProgram *shader;
    try {
        tex = new GraphicsEngine::Texture(GraphicsEngine::LocalFilePath("textures/test.png").c_str());
        shader = new GraphicsEngine::PerspectiveShaderProgram(
            GraphicsEngine::LocalFilePath("shaders/triangle.vs.glsl").c_str(),
            GraphicsEngine::LocalFilePath("shaders/triangle.fs.glsl").c_str(),
            "uMVPMatrix", "uMVMatrix", "uNormalMatrix");
        material = new GraphicsEngine::Material(tex , shader);
    } catch(GraphicsEngine::InitialisationException error) {
        std::cout << error.what();
        //return 0;
    }
    std::cout << "Done\nGEC Mesh" << std::endl;
    
    GraphicsEngine::Controller::instance()->printInfos();
    
    // Hello triangle
    std::vector<GraphicsEngine::Vertex> helloTriangle;
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(-0.5f,0.f,-1.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f,0.f)));
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(0.5f,0.f,-1.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.5f,0.f)));
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(0.f,1.f,-1.f), glm::vec3(0.f,0.f,1.f), glm::vec2(0.f,1.0f)));

    std::cout << "Done\nGEC Object" << std::endl;
    GraphicsEngine::Object *object = new GraphicsEngine::Object(new GraphicsEngine::Mesh(helloTriangle), material);
    
    GraphicsEngine::Controller::instance()->activeScene()->add(object);

    std::cout << "Done\nGEC Event" << std::endl;
    testQuit shouldKeepRunning;
    GraphicsEngine::EventManager::instance()->subscribe(&shouldKeepRunning);
    testKeyboard keyboardListener;
    keyboardListener.cameraToMove = &camera;
    GraphicsEngine::EventManager::instance()->subscribe(&keyboardListener);

    std::cout << "Done\nGEC Render" << std::endl;
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
