/**
 * \file GameController.cpp
 */

#include "GameController.hpp"


// creates scene and load objects
void GameController::initializeScene() {
    initializeDebugGrid();

    // 2D context
    std::unique_ptr<GraphicsEngine::Canvas> canvas(new GraphicsEngine::Canvas());
    GraphicsEngine::Controller::instance()->loadGUI(canvas);

    // 3D context
    std::unique_ptr<GraphicsEngine::Scene> scene(new GraphicsEngine::Scene(m_playerPointOfView));
    GraphicsEngine::Controller::instance()->loadScene(scene);

    // create objects
    std::shared_ptr<GraphicsEngine::Object3D> playerModel = m_currentGame->playerModel();
    m_skybox = createSkyBox();
    m_chunk = createChunk();

    // skybox max scale before clipping out of far-field
    m_skybox->scale(glm::vec3(3.14f));

    // adds objects in the scene
    GraphicsEngine::Controller::instance()->activeScene()->add(playerModel);
    GraphicsEngine::Controller::instance()->activeScene()->add(m_skybox);
}



void GameController::setup() {
    // initialize framworks and windows
    GraphicsEngine::Controller::instance()->setup();
    GraphicsEngine::Controller::instance()->printInfos();

    Entity::loadObject();

    m_currentGame = std::unique_ptr<Game>(new Game);

    // create scene
    initializeScene();


    // preload terrain
    for (size_t i = 0; i < m_CHUNK_PRELOADING_COUNT; i++) {
        loadNewChunk();
        m_currentGame->terrain().progress(m_CHUNK_LENGTH/m_CHUNK_FRAME_DURATION);
    }

    // subscribe event manager
    Events::Manager::instance()->subscribe((QuitEventObserver*) this);
    Events::Manager::instance()->subscribe((KeyboardEventObserver*) this);
    Events::Manager::instance()->subscribe((MouseEventObserver*) this);
}



// game loop
bool GameController::loop() {
    // read the time at the start of the game loop
    Uint32 startTime = SDL_GetTicks();

    // framerate 60 frames per seconds
    const float FRAMERATE = 60;

    // compute current chunk progress
    m_chunkframe ++;
    m_chunkframe %= m_CHUNK_FRAME_DURATION;

    if(m_chunkframe == 0) {
        loadNewChunk();
        m_currentGame->terrain().nextChunk();
    }

    m_currentGame->terrain().progress(m_CHUNK_LENGTH/m_CHUNK_FRAME_DURATION);

    GraphicsEngine::Animation::updateAnimations();

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



void GameController::loadNewChunk() {
    Entity* left = new Entity();
    Entity* middle = new Entity();
    Entity* right = new Entity();

    m_currentGame->terrain().loadChunk(left,middle, right, -m_CHUNK_LENGTH * m_CHUNK_PRELOADING_COUNT);
    GraphicsEngine::Controller::instance()->activeScene()->add(left->object());
    GraphicsEngine::Controller::instance()->activeScene()->add(middle->object());
    GraphicsEngine::Controller::instance()->activeScene()->add(right->object());
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

        case 'z': m_currentGame->callInput(Controls::UP); break;
        case 'q': m_currentGame->callInput(Controls::LEFT); break;
        case 'd': m_currentGame->callInput(Controls::RIGHT); break;
        case 's': m_currentGame->callInput(Controls::DOWN); break;

        case 'g':
            std::cout << "Toggling Grid " << (m_debugGrid? "off" : "on") << std::endl;
            if (m_debugGrid){
                m_debugGrid.reset();
                // GraphicsEngine::Controller::instance()->activeScene()->remove(m_debugGrid);
            } else {
                m_debugGrid = initializeDebugGrid();
                GraphicsEngine::Controller::instance()->activeScene()->add(m_debugGrid);
            }
            break;
    }
};


void GameController::keyPressHandler(std::set<unsigned char> &pressedKeys) {
    const float KEYBOARD_CAMERA_CONTROL_SPEED = 0.1;
    for (unsigned char key : pressedKeys) {
        switch (key) {


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

            default:
                //std::cout << "char: " << key << " int: " << (int) key << std::endl;
                break;
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





// make grid
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


// make skybox
std::shared_ptr<GraphicsEngine::Object3D> GameController::createSkyBox() {
    GraphicsEngine::LocalFilePath chunkmesh("assets/models/skyboxtest.obj");
    GraphicsEngine::LocalFilePath chunktex("assets/textures/cubemap_skybox.png");
    GraphicsEngine::LocalFilePath chunkvs("shaders/perspective.vs.glsl");
    GraphicsEngine::LocalFilePath chunkfs("shaders/flatTexture.fs.glsl");
    return createObject3D(chunkmesh, chunktex, chunkvs, chunkfs);
}


// make chunk
std::shared_ptr<GraphicsEngine::Object3D> GameController::createChunk() {
    GraphicsEngine::LocalFilePath chunkmesh("assets/models/cube.obj");
    GraphicsEngine::LocalFilePath chunktex("assets/textures/cubemap_a.png");
    GraphicsEngine::LocalFilePath chunkvs("shaders/perspective.vs.glsl");
    GraphicsEngine::LocalFilePath chunkfs("shaders/flatTexture.fs.glsl");

    return createObject3D(chunkmesh, chunktex, chunkvs, chunkfs);
}


// singleton

GameController* GameController::s_controllerInstance = nullptr;

GameController* GameController::instance() {
    if (s_controllerInstance == nullptr)
        s_controllerInstance = new GameController();
    return s_controllerInstance;
}



//Loading assets and shaders from relative filepaths to create a 3D object
std::shared_ptr<GraphicsEngine::Object3D> GameController::createObject3D(GraphicsEngine::LocalFilePath &meshPath, GraphicsEngine::LocalFilePath &textureImagePath,GraphicsEngine::LocalFilePath &vertexShaderPath, GraphicsEngine::LocalFilePath &fragmentShaderPath) {
    try {
        return std::make_shared<GraphicsEngine::Object3D>
        (
         std::make_shared<GraphicsEngine::ImportedMesh>(meshPath),
         std::make_shared<GraphicsEngine::Material>(
            std::make_shared<GraphicsEngine::PerspectiveShaderProgram>(vertexShaderPath, fragmentShaderPath,"uMVPMatrix", "uMVMatrix", "uNormalMatrix"), std::make_shared<GraphicsEngine::Texture>(textureImagePath)
            )
         );
    } catch(GraphicsEngine::InitialisationException error) {
        std::cout << error.what();
        return nullptr;
    }
}


//CONSTRUCTOR
GameController::GameController() {}
