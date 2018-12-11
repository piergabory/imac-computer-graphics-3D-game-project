#include "GameController.hpp"

void GameController::linkEventObserver() {
    GraphicsEngine::EventManager::instance()->subscribe((QuitEventObserver*) this);
    GraphicsEngine::EventManager::instance()->subscribe((KeyboardEventObserver*) this);
    GraphicsEngine::EventManager::instance()->subscribe((MouseEventObserver*) this);
}



void GameController::initializeScene() {
    GraphicsEngine::Material *material;
    GraphicsEngine::Texture *tex;
    GraphicsEngine::PerspectiveShaderProgram *shader;
    GraphicsEngine::Scene *scene = new GraphicsEngine::Scene(&m_playerPointOfView);

    GraphicsEngine::Controller::instance()->loadScene(scene);

    // load shaders
    try {
        tex = new GraphicsEngine::Texture(GraphicsEngine::LocalFilePath("textures/test.png").c_str());
        shader = new GraphicsEngine::PerspectiveShaderProgram(
          GraphicsEngine::LocalFilePath("shaders/triangle.vs.glsl").c_str(),
          GraphicsEngine::LocalFilePath("shaders/triangle.fs.glsl").c_str(),
          "uMVPMatrix", "uMVMatrix", "uNormalMatrix");
        material = new GraphicsEngine::Material(shader, tex);
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

    GraphicsEngine::Controller::instance()->activeScene()->add(object);

    try {
        tex = new GraphicsEngine::Texture(GraphicsEngine::LocalFilePath("textures/test.png").c_str());
        shader = new GraphicsEngine::PerspectiveShaderProgram(
                                                              GraphicsEngine::LocalFilePath("shaders/triangle.vs.glsl").c_str(),
                                                              GraphicsEngine::LocalFilePath("shaders/triangle.fs.glsl").c_str(),
                                                              "uMVPMatrix", "uMVMatrix", "uNormalMatrix");
        material = new GraphicsEngine::Material(shader, tex);
    } catch(GraphicsEngine::InitialisationException error) {
        std::cout << error.what();
    }

    std::vector<GraphicsEngine::Vertex> grid;
    float gridScale = 5;
    uint gridsize = 30;
    for (uint i = 0; i < gridsize; ++i) {
        float position = i * 2.f / gridsize - 1;
        grid.push_back(GraphicsEngine::Vertex(gridScale * glm::vec3(position,0.f,1.f), glm::vec3(0), glm::vec2(0)));
        grid.push_back(GraphicsEngine::Vertex(gridScale * glm::vec3(position,0.f,-1.f), glm::vec3(0), glm::vec2(0)));
        grid.push_back(GraphicsEngine::Vertex(gridScale * glm::vec3(1.f,0.f,position), glm::vec3(0), glm::vec2(0)));
        grid.push_back(GraphicsEngine::Vertex(gridScale * glm::vec3(-1.f,0.f,position), glm::vec3(0), glm::vec2(0)));
    }
    GraphicsEngine::Material *wireframe = new GraphicsEngine::Material(new GraphicsEngine::PerspectiveShaderProgram(GraphicsEngine::LocalFilePath("shaders/wireframe.vs.glsl").c_str(), GraphicsEngine::LocalFilePath("shaders/wireframe.fs.glsl").c_str(), "uMVPMatrix", "uMVMatrix", "uNormalMatrix"));
    GraphicsEngine::Object *gridobj = new GraphicsEngine::Object(new GraphicsEngine::Mesh(grid, GL_LINES), wireframe);

    GraphicsEngine::Controller::instance()->activeScene()->add(gridobj);
}



void GameController::setup() {
    GraphicsEngine::Controller::instance()->setup();
    GraphicsEngine::Controller::instance()->printInfos();

    initializeScene();
    linkEventObserver();
}



bool GameController::loop() {

    Uint32 startTime = SDL_GetTicks();

    handlePressedKey();
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



void GameController::handlePressedKey() {
    const float KEYBOARD_CAMERA_CONTROL_SPEED = 0.1;

    // check if debug shortcuts is activated (CTRL-SHIFT):
    if (m_pressedKeys.find(225) != m_pressedKeys.end() && m_pressedKeys.find(224) != m_pressedKeys.end()) {
        for (unsigned char key : m_pressedKeys) {
            switch (key) {
                // we ignore Shift and Ctrl
                case 224: case 225: break;

                case 'g':
                    std::cout << "Toggling Grid" << std::endl;
                    break;

                default:
                    std::cout << "DEBUG! ";
                    std::cout << "char: " << key << " int: " << (int) key << std::endl;
                    break;
            }
        }
    } else {
        for (unsigned char key : m_pressedKeys) {
            switch (key) {

                // Forward
                case 'z':
                    m_playerPointOfView.move(glm::vec3(0,0,-KEYBOARD_CAMERA_CONTROL_SPEED));
                    break;

                // Left
                case 'q':
                    m_playerPointOfView.move(glm::vec3(KEYBOARD_CAMERA_CONTROL_SPEED,0,0));
                    break;

                // Backward
                case 's':
                    m_playerPointOfView.move(glm::vec3(0,0,KEYBOARD_CAMERA_CONTROL_SPEED));
                    break;

                // Right
                case 'd':
                    m_playerPointOfView.move(glm::vec3(-KEYBOARD_CAMERA_CONTROL_SPEED,0,0));
                    break;

                // Up
                case 'w':
                    m_playerPointOfView.move(glm::vec3(0,-KEYBOARD_CAMERA_CONTROL_SPEED,0));
                    break;

                // Down
                case 'x':
                    m_playerPointOfView.move(glm::vec3(0,KEYBOARD_CAMERA_CONTROL_SPEED,0));
                    break;

                // Rotate right
                case 'e':
                    m_playerPointOfView.pan(glm::vec3(0,1,0), KEYBOARD_CAMERA_CONTROL_SPEED);
                    break;

                // Rotate left
                case 'a':
                    m_playerPointOfView.pan(glm::vec3(0,-1,0), KEYBOARD_CAMERA_CONTROL_SPEED);
                    break;

                // Rotate up
                case 'r':
                    m_playerPointOfView.pan(glm::vec3(1,0,0), KEYBOARD_CAMERA_CONTROL_SPEED);
                    break;

                // rotate down
                case 'f':
                    m_playerPointOfView.pan(glm::vec3(-1,0,0), KEYBOARD_CAMERA_CONTROL_SPEED);
                    break;

                // '0/à' key (not the numpad)
                case '0':
                    m_playerPointOfView.resetPosition();
                    break;

                // escape key
                case 27:
                    SDL_CaptureMouse(SDL_FALSE);
                    break;

                default: std::cout << "char: " << key << " int: " << (int) key << std::endl; break;
            }
        }
    }
}


void GameController::mouseMoveHandler(float relativeXMovement,float relativeYMovement) {
    const float MOUSEMOVE_SCALING = 0.006;
    m_playerPointOfView.pan(glm::vec3(0,-1,0), relativeXMovement * MOUSEMOVE_SCALING);
    m_playerPointOfView.pan(glm::vec3(1,0,0), relativeYMovement * MOUSEMOVE_SCALING);
}


void GameController::mouseWheelHandler(float deltaX, float deltaY) {
    const float MOUSEWHEEL_SCALING = 0.1;
    m_playerPointOfView.move(glm::vec3(MOUSEWHEEL_SCALING * deltaX, 0, MOUSEWHEEL_SCALING * deltaY));
}

void GameController::mouseReleaseHandler(unsigned char button) {
    SDL_CaptureMouse(SDL_TRUE);
}


GameController* GameController::m_controllerInstance = nullptr;

GameController* GameController::instance() {
    if (m_controllerInstance == nullptr)
        m_controllerInstance = new GameController();
    return m_controllerInstance;
}
