#include "GameController.hpp"

// subscribe the game controller to the SDL event manager.
void GameController::linkEventObserver() {
    Events::Manager::instance()->subscribe((QuitEventObserver*) this);
    Events::Manager::instance()->subscribe((KeyboardEventObserver*) this);
    Events::Manager::instance()->subscribe((MouseEventObserver*) this);
}


// creates scene and load objects
void GameController::initializeScene() {
    createObjects();

    std::unique_ptr<GraphicsEngine::Canvas> canvas(new GraphicsEngine::Canvas());
    GraphicsEngine::Controller::instance()->loadGUI(canvas);
    GraphicsEngine::Controller::instance()->activeGUI()->add(m_testSquare);

    std::unique_ptr<GraphicsEngine::Scene>  scene(new GraphicsEngine::Scene(m_playerPointOfView));
    GraphicsEngine::Controller::instance()->loadScene(scene);
    

    
    GraphicsEngine::Controller::instance()->activeScene()->add(m_nanosuit);
    
    GraphicsEngine::Controller::instance()->activeScene()->add(m_skybox);
    
    GraphicsEngine::Controller::instance()->activeScene()->add(m_anotherHelloTriangle);
    
}



void GameController::setup() {
    // initialize framworks and windows
    GraphicsEngine::Controller::instance()->setup();
    GraphicsEngine::Controller::instance()->printInfos();

    // create scene
    initializeScene();

    // subscribe event manager
    linkEventObserver();
}



// game loop
bool GameController::loop() {
    // framerate 60 frames per seconds
    const float FRAMERATE = 60;

    // read the time at the start of the game loop
    Uint32 startTime = SDL_GetTicks();

    // respond to events
    // TODO utiliser l'EventManager
    handlePressedKey();

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
    m_pressedKeys.erase(keycode);
    // check if debug shortcuts is activated (CTRL-SHIFT):
    if (m_pressedKeys.find(225) != m_pressedKeys.end() && m_pressedKeys.find(224) != m_pressedKeys.end()) {

        switch (keycode) {
                // we ignore Shift and Ctrl
            case 224: case 225: break;

            case 'g':
                m_isDebugGridActive = !m_isDebugGridActive;
                std::cout << "Toggling Grid " << (m_isDebugGridActive? "on" : "off") << std::endl;
                if (m_isDebugGridActive) {
                    GraphicsEngine::Controller::instance()->activeScene()->remove(m_debugGrid);
                } else {
                    GraphicsEngine::Controller::instance()->activeScene()->add(m_debugGrid);
                }

                break;

            default:
                std::cout << "DEBUG! ";
                std::cout << "char: " << keycode << " int: " << (int) keycode << std::endl;
                break;
        }
    }
};



void GameController::keyDownHandler(unsigned char keycode) {
    m_pressedKeys.insert(keycode);
};



void GameController::handlePressedKey() {
    const float KEYBOARD_CAMERA_CONTROL_SPEED = 0.1;

    for (unsigned char key : m_pressedKeys) {
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

void GameController::createObjects() {
    // create meshes
    std::vector<GraphicsEngine::Vertex3D> grid, helloTriangle, skybox;

    // hello triangle
    helloTriangle.push_back(GraphicsEngine::Vertex3D(glm::vec3(-0.5f,0.f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f,0.f)));
    helloTriangle.push_back(GraphicsEngine::Vertex3D(glm::vec3(0.5f,0.f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.5f,1.f)));
    helloTriangle.push_back(GraphicsEngine::Vertex3D(glm::vec3(0.f,1.f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(1.f,0.0f)));

    // debug grid
    float gridScale = 5;
    uint gridsize = 30;
    for (uint i = 0; i < gridsize; ++i) {
        float position = i * 2.f / gridsize - 1;
        grid.push_back(GraphicsEngine::Vertex3D(gridScale * glm::vec3(position,0.f,1.f), glm::vec3(0), glm::vec2(0)));
        grid.push_back(GraphicsEngine::Vertex3D(gridScale * glm::vec3(position,0.f,-1.f), glm::vec3(0), glm::vec2(0)));
        grid.push_back(GraphicsEngine::Vertex3D(gridScale * glm::vec3(1.f,0.f,position), glm::vec3(0), glm::vec2(0)));
        grid.push_back(GraphicsEngine::Vertex3D(gridScale * glm::vec3(-1.f,0.f,position), glm::vec3(0), glm::vec2(0)));
    }


    try {
        // create test texture
        std::shared_ptr<GraphicsEngine::Texture> testTexture = std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("textures/test.png"));
        


        // create objects
        m_helloTriangle = std::make_shared<GraphicsEngine::Object3D>(std::make_shared<GraphicsEngine::Mesh3D>(helloTriangle), std::make_shared<GraphicsEngine::Material>(std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(GraphicsEngine::LocalFilePath("shaders/triangle.vs.glsl"), GraphicsEngine::LocalFilePath("shaders/triangle.fs.glsl"), "uMVPMatrix", "uMVMatrix", "uNormalMatrix"), testTexture));

        m_anotherHelloTriangle = std::make_shared<GraphicsEngine::Object3D>(*m_helloTriangle);
        

     
        //Create nanosuit object 
        std::shared_ptr<GraphicsEngine::Texture> nanoTexture = std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("assets/nanosuit/body_showroom_spec.png"));
        
        GraphicsEngine::LocalFilePath nanopath("assets/nanosuit/nanosuit.obj");
        m_nanosuit = std::make_shared<GraphicsEngine::Object3D>(std::make_shared<GraphicsEngine::ImportedMesh>(nanopath), std::make_shared<GraphicsEngine::Material>(std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(GraphicsEngine::LocalFilePath("shaders/triangle.vs.glsl"), GraphicsEngine::LocalFilePath("shaders/triangle.fs.glsl"), "uMVPMatrix", "uMVMatrix", "uNormalMatrix"), nanoTexture));
        
        //create Skybox
        std::shared_ptr<GraphicsEngine::Texture> skyTexture = std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("textures/cubemap_skybox.jpg"));
        GraphicsEngine::LocalFilePath skyboxpath("assets/skyboxtest.obj");
        m_skybox = std::make_shared<GraphicsEngine::Object3D>(std::make_shared<GraphicsEngine::ImportedMesh>(skyboxpath), std::make_shared<GraphicsEngine::Material>(std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(GraphicsEngine::LocalFilePath("shaders/triangle.vs.glsl"), GraphicsEngine::LocalFilePath("shaders/triangle.fs.glsl"), "uMVPMatrix", "uMVMatrix", "uNormalMatrix"), skyTexture));


        
        m_debugGrid = std::make_shared<GraphicsEngine::Object3D>(std::make_shared<GraphicsEngine::Mesh3D>(grid , GL_LINES), std::make_shared<GraphicsEngine::Material>(std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(GraphicsEngine::LocalFilePath("shaders/wireframe.vs.glsl"), GraphicsEngine::LocalFilePath("shaders/wireframe.fs.glsl"), "uMVPMatrix", "uMVMatrix", "uNormalMatrix")));


        std::function<void(GraphicsEngine::Button*, unsigned char)> callback = [](GraphicsEngine::Button* target, unsigned char mouseButton) -> void {
            std::cout << "you clicked the button" << std::endl;
        };

        m_testSquare = std::make_shared<GraphicsEngine::Button>(
            glm::vec2(0, 0),
            glm::vec2(0.1, 0.1),
            std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("textures/test.png")),
            callback
        );

    } catch(GraphicsEngine::InitialisationException error) {
        std::cout << error.what();
    }

    m_player= new Player(*m_helloTriangle, 0.5f);
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


GameController* GameController::s_controllerInstance = nullptr;

GameController* GameController::instance() {
    if (s_controllerInstance == nullptr)
        s_controllerInstance = new GameController();
    return s_controllerInstance;
}

GameController::GameController() {
}
