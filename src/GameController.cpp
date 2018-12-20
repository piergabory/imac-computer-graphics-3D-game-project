#include "GameController.hpp"


// creates scene and load objects
void GameController::initializeScene() {
    initializeDebugGrid();

    std::unique_ptr<GraphicsEngine::Canvas> canvas(new GraphicsEngine::Canvas());
    GraphicsEngine::Controller::instance()->loadGUI(canvas);

    std::unique_ptr<GraphicsEngine::Scene>  scene(new GraphicsEngine::Scene(m_playerPointOfView));
    GraphicsEngine::Controller::instance()->loadScene(scene);


    // create objects
    std::shared_ptr<GraphicsEngine::Object3D> playerModel = m_currentGame->playerModel();
    m_skybox = createSkyBox();

    // adds objects in the scene
    GraphicsEngine::Controller::instance()->activeScene()->add(playerModel);
    GraphicsEngine::Controller::instance()->activeScene()->add(m_skybox);
}



void GameController::setup() {
    // initialize framworks and windows
    GraphicsEngine::Controller::instance()->setup();
    GraphicsEngine::Controller::instance()->printInfos();


    m_currentGame = std::unique_ptr<Game>(new Game);

    // create scene
    initializeScene();

    // subscribe event manager
    Events::Manager::instance()->subscribe((QuitEventObserver*) this);
    Events::Manager::instance()->subscribe((KeyboardEventObserver*) this);
    Events::Manager::instance()->subscribe((MouseEventObserver*) this);
}



// game loop
bool GameController::loop() {
    // framerate 60 frames per seconds
    const float FRAMERATE = 60;

    // read the time at the start of the game loop
    Uint32 startTime = SDL_GetTicks();

    // start new render cycle
    GraphicsEngine::Controller::instance()->render();

    // fetches new events
    Events::Manager::instance()->pollEvents();

    // calculate the time spent since the start of the game loop
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < 1000 / FRAMERATE) {
        // wait a while before the next frame, in order to keep a consistent framerate.
        SDL_Delay(1000 / FRAMERATE - elapsedTime);
    }

    return m_isRunning;
}



void GameController::quitEventHandler() {
    m_isRunning = false;
    GraphicsEngine::Controller::instance()->close();
}


// a déolacer dans l'EventManager
void GameController::keyRealeaseHandler(unsigned char keycode) {
    // check if debug shortcuts is activated (CTRL-SHIFT):
    switch (keycode) {
            // we ignore Shift and Ctrl
        case 224: case 225: break;

        case 'g':
            std::cout << "Toggling Grid " << (m_isDebugGridActive? "off" : "on") << std::endl;
            if (m_debugGrid){
                m_debugGrid.reset();
                GraphicsEngine::Controller::instance()->activeScene()->remove(m_debugGrid);
            } else {
                m_debugGrid = initializeDebugGrid();
                GraphicsEngine::Controller::instance()->activeScene()->add(m_debugGrid);
            }
            m_isDebugGridActive = !m_isDebugGridActive;
            break;

        default:
            std::cout << "DEBUG! ";
            std::cout << "char: " << keycode << " int: " << (int) keycode << std::endl;
            break;
    }
};


void GameController::keyPressHandler(std::set<unsigned char> &pressedKeys) {
    const float KEYBOARD_CAMERA_CONTROL_SPEED = 0.1;
    for (unsigned char key : pressedKeys) {
        switch (key) {
            case 224: case 225: break;

                // Forward
            case 'z':
                m_playerPointOfView.move(glm::vec3(0,0,-KEYBOARD_CAMERA_CONTROL_SPEED));
                break;

                // Left
            case 'q':
                m_playerPointOfView.move(glm::vec3(-KEYBOARD_CAMERA_CONTROL_SPEED,0,0));
                break;

                // Backward
            case 's':
                m_playerPointOfView.move(glm::vec3(0,0,KEYBOARD_CAMERA_CONTROL_SPEED));
                break;

                // Right
            case 'd':
                m_playerPointOfView.move(glm::vec3(KEYBOARD_CAMERA_CONTROL_SPEED,0,0));
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

                // '0' key (not the numpad)
            case '0':
                m_playerPointOfView.resetPosition();
                break;

                // escape key
            case 27:
                SDL_CaptureMouse(SDL_FALSE);
                SDL_ShowCursor(SDL_ENABLE);
                break;

            default: std::cout << "char: " << key << " int: " << (int) key << std::endl; break;
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
    SDL_ShowCursor(SDL_DISABLE);
}

std::shared_ptr<GraphicsEngine::Object3D> GameController::initializeDebugGrid() {
    float gridScale = 5;
    uint gridsize = 30;

    // create debug grid mesh
    std::vector<GraphicsEngine::Vertex3D> grid;
    grid.reserve(4 * gridsize);
    for (uint i = 0; i < gridsize; ++i) {
        float position = i * 2.f / gridsize - 1;
        grid.push_back(GraphicsEngine::Vertex3D(gridScale * glm::vec3(position,0.f,1.f), glm::vec3(0), glm::vec2(0)));
        grid.push_back(GraphicsEngine::Vertex3D(gridScale * glm::vec3(position,0.f,-1.f), glm::vec3(0), glm::vec2(0)));
        grid.push_back(GraphicsEngine::Vertex3D(gridScale * glm::vec3(1.f,0.f,position), glm::vec3(0), glm::vec2(0)));
        grid.push_back(GraphicsEngine::Vertex3D(gridScale * glm::vec3(-1.f,0.f,position), glm::vec3(0), glm::vec2(0)));
    }

    try {
        // create debug object
        return std::make_shared<GraphicsEngine::Object3D>(
                                                          std::make_shared<GraphicsEngine::Mesh3D>(grid , GL_LINES),
                                                          std::make_shared<GraphicsEngine::Material>(
                                                                                                     std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(
                                                                                                                                                                GraphicsEngine::LocalFilePath("shaders/perspective.vs.glsl"),
                                                                                                                                                                GraphicsEngine::LocalFilePath("shaders/flatColor.fs.glsl")
                                                                                                                                                                )
                                                                                                     )
                                                          );
    } catch(GraphicsEngine::InitialisationException error) {
        std::cerr << error.what() << std::endl;
        return nullptr;
    }
}


std::shared_ptr<GraphicsEngine::Object3D> GameController::createSkyBox() {
    try {
        return std::make_shared<GraphicsEngine::Object3D>(std::make_shared<GraphicsEngine::ImportedMesh>(GraphicsEngine::LocalFilePath("assets/skyboxtest.obj")), std::make_shared<GraphicsEngine::Material>(std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(GraphicsEngine::LocalFilePath("shaders/perspective.vs.glsl"), GraphicsEngine::LocalFilePath("shaders/flatTexture.fs.glsl"), "uMVPMatrix", "uMVMatrix", "uNormalMatrix"), std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("textures/cubemap_skybox.jpg"))));
    } catch(GraphicsEngine::InitialisationException error) {
        std::cout << error.what();
        return nullptr;
    }
}


GameController* GameController::s_controllerInstance = nullptr;

GameController* GameController::instance() {
    if (s_controllerInstance == nullptr)
        s_controllerInstance = new GameController();
    return s_controllerInstance;
}

GameController::GameController() {}
