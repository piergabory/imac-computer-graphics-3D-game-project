#include "GameController.hpp"

void GameController::linkEventObserver() {
    GraphicsEngine::EventManager::instance()->subscribe((QuitEventObserver*) m_controllerInstance);
    GraphicsEngine::EventManager::instance()->subscribe((KeyboardEventObserver*) m_controllerInstance);
}



void GameController::initializeScene() {
    GraphicsEngine::Camera camera;
    GraphicsEngine::Material *material;
    GraphicsEngine::Texture *tex;
    GraphicsEngine::PerspectiveShaderProgram *shader;
    GraphicsEngine::Scene *scene = new GraphicsEngine::Scene(&camera);

    GraphicsEngine::Controller::instance()->loadScene(scene);

    // load shaders
    try {
        tex = new GraphicsEngine::Texture(GraphicsEngine::LocalFilePath("textures/test.png").c_str());
        shader = new GraphicsEngine::PerspectiveShaderProgram(
          GraphicsEngine::LocalFilePath("shaders/triangle.vs.glsl").c_str(),
          GraphicsEngine::LocalFilePath("shaders/triangle.fs.glsl").c_str(),
          "uMVPMatrix", "uMVMatrix", "uNormalMatrix");
        material = new GraphicsEngine::Material(tex , shader);
    } catch(GraphicsEngine::InitialisationException error) {
        std::cout << error.what();
    }

    // Hello triangle
    std::vector<GraphicsEngine::Vertex> helloTriangle;
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(-0.5f,0.f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f,0.f)));
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(0.5f,0.f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.5f,0.f)));
    helloTriangle.push_back(GraphicsEngine::Vertex(glm::vec3(0.f,1.f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(0.f,1.0f)));

    GraphicsEngine::Object *object = new GraphicsEngine::Object(new GraphicsEngine::Mesh(helloTriangle), material);
    object->scale(glm::vec3(0.3));
    object->translate(glm::vec3(0,0,-2));

    GraphicsEngine::Controller::instance()->activeScene()->add(object);
}



void GameController::setup() {
    GraphicsEngine::Controller::instance()->setup();
    GraphicsEngine::Controller::instance()->printInfos();

    initializeScene();
    linkEventObserver();
}



bool GameController::loop() {

    Uint32 startTime = SDL_GetTicks();

    GraphicsEngine::Controller::instance()->render();
    GraphicsEngine::Controller::instance()->pollEvents();

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < 50) {
        SDL_Delay(50 - elapsedTime);
    }

    return m_isRunning;
}



void GameController::quitEventHandler() {
    m_isRunning = false;
    GraphicsEngine::Controller::instance()->close();
}



void GameController::keyRealeaseHandler(unsigned char keycode) {
    m_pressedKeys.erase(keycode);
};



void GameController::keyDownHandler(unsigned char keycode) {
    m_pressedKeys.insert(keycode);
};



GameController* GameController::m_controllerInstance = nullptr;

GameController* GameController::instance() {
    if (m_controllerInstance == nullptr)
        m_controllerInstance = new GameController();
    return m_controllerInstance;
}
