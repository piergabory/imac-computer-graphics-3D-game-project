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
    m_playerPointOfView = std::make_shared<GraphicsEngine::Camera>();
    m_playerPointOfView->place(glm::vec3(0,2,0));
    m_playerPointOfView->rotate(glm::radians(10.f), glm::vec3(1,0,0));
    std::unique_ptr<GraphicsEngine::Scene> scene(new GraphicsEngine::Scene(m_playerPointOfView));
    GraphicsEngine::Controller::instance()->loadScene(scene);

    // create objects
    std::shared_ptr<GraphicsEngine::Object3D> playerModel = m_currentGame->playerModel();
    m_skybox = createSkyBox();
    m_chunk = createChunk();
    createMenu();
    createCursor();

    // skybox max scale before clipping out of far-field
    m_skybox->scale(glm::vec3(3.14f));

    // adds objects in the scene
    GraphicsEngine::Controller::instance()->activeScene()->add(playerModel);
    GraphicsEngine::Controller::instance()->activeScene()->add(m_skybox);
    
    GraphicsEngine::Controller::instance()->activeGUI()->add(m_menu->elements());

    

}



void GameController::setup() {
    // initialize framworks and windows
    GraphicsEngine::Controller::instance()->setup();
    GraphicsEngine::Controller::instance()->printInfos();

    m_currentGame = std::unique_ptr<GameModel::Game>(new GameModel::Game);

    // create scene
    initializeScene();

    GameModel::Chunk* preloadedChunk;
    for (uint i = 0; i < m_CHUNK_PRELOADING_COUNT; ++i) {
        preloadedChunk = new GameModel::Chunk();
        for(std::shared_ptr<GraphicsEngine::Object3D> object : preloadedChunk->objects()) {
            GraphicsEngine::Controller::instance()->activeScene()->add(object);
        };
        m_currentGame->terrain().loadChunk(preloadedChunk);
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
        m_chunkCycle ++;
        loadNewChunk();
        m_currentGame->nextChunk();
    }

    m_currentGame->terrain().progress(1.f/m_CHUNK_FRAME_DURATION);

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
    GameModel::Chunk* chunk;

    if (m_chunkCycle % 40 == 0) {
        chunk = new GameModel::TurningChunk(GameModel::TurnDirection::LEFT,
                                 static_cast< std::shared_ptr<GraphicsEngine::Animatable> >(m_playerPointOfView),
                                 static_cast< std::shared_ptr<GraphicsEngine::Animatable> >(m_currentGame->playerModel()));
    } else if(m_chunkCycle % 50 == 0) {
        chunk = new GameModel::TurningChunk(GameModel::TurnDirection::RIGHT,
                                            static_cast< std::shared_ptr<GraphicsEngine::Animatable> >(m_playerPointOfView),
                                 static_cast< std::shared_ptr<GraphicsEngine::Animatable> >(m_currentGame->playerModel()));
    } else {
        chunk = new GameModel::Chunk(new GameModel::Entity(), new GameModel::Entity(), new GameModel::Entity());
    }
    
    m_currentGame->terrain().loadChunk(chunk);
    for(std::shared_ptr<GraphicsEngine::Object3D> object : chunk->objects()) {
        GraphicsEngine::Controller::instance()->activeScene()->add(object);
    };
}



void GameController::quitEventHandler() {
    m_isRunning = false;
    GraphicsEngine::Controller::instance()->close();
}


// a déolacer dans l'EventManager
void GameController::keyRealeaseHandler(const SDL_Keycode keycode) {
    // check if debug shortcuts is activated (CTRL-SHIFT):
    switch (keycode) {
            // escape key
        case SDLK_ESCAPE:
            SDL_CaptureMouse(SDL_FALSE);
            SDL_ShowCursor(SDL_ENABLE);
            break;

        case SDLK_z: m_currentGame->callInput(GameModel::Controls::UP); break;
        case SDLK_q: m_currentGame->callInput(GameModel::Controls::LEFT); break;
        case SDLK_d: m_currentGame->callInput(GameModel::Controls::RIGHT); break;
        case SDLK_s: m_currentGame->callInput(GameModel::Controls::DOWN); break;

        case SDLK_c:
            switch (m_cameraBehavior) {
                case CameraBehaviors::LOCKED:
                    m_cameraBehavior = CameraBehaviors::FOLOW_PLAYER;
                    std::cout << "Camera set to FOLOW PLAYER" << std::endl;
                    break;

                case CameraBehaviors::FOLOW_PLAYER:
                    m_cameraBehavior = CameraBehaviors::FREE;
                    std::cout << "Camera set to LOCKED" << std::endl;
                    break;

                case CameraBehaviors::FREE:
                    m_cameraBehavior = CameraBehaviors::LOCKED;
                    std::cout << "Camera set to FREE" << std::endl;
                    break;

                default: assert(false && "Bad CameraBehavior enum");
            }
            break;

        case SDLK_g:
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


void GameController::keyPressHandler(const std::set<const SDL_Keycode> &pressedKeys) {
    for (SDL_Keycode key : pressedKeys) {
        cameraMoves(key);
    }
}



void GameController::mouseMoveHandler(float relativeXMovement,float relativeYMovement) {
    const float MOUSEMOVE_SCALING = 0.006;
    m_playerPointOfView->rotate(relativeXMovement * MOUSEMOVE_SCALING, glm::vec3(0,-1,0));
    m_playerPointOfView->rotate(relativeYMovement * MOUSEMOVE_SCALING, glm::vec3(1,0,0));
}


void GameController::mouseWheelHandler(float deltaX, float deltaY) {
    const float MOUSEWHEEL_SCALING = 0.1;
    m_playerPointOfView->translate(glm::vec3(MOUSEWHEEL_SCALING * deltaX, 0, MOUSEWHEEL_SCALING * deltaY));
}


void GameController::mouseReleaseHandler(const unsigned char button) {
    SDL_CaptureMouse(SDL_TRUE);
    SDL_ShowCursor(SDL_ENABLE); ///TODO - put back to disable
}


void GameController::cameraMoves(const SDL_Keycode key) {
    const float KEYBOARD_CAMERA_CONTROL_SPEED = 0.1;
    if (m_cameraBehavior == CameraBehaviors::FREE) switch(key) {
            // Up
        case 'i':
            m_playerPointOfView->translate(glm::vec3(0,-KEYBOARD_CAMERA_CONTROL_SPEED,0));
            break;

            // Down
        case 'k':
            m_playerPointOfView->translate(glm::vec3(0,KEYBOARD_CAMERA_CONTROL_SPEED,0));
            break;

            // left
        case 'j':
            m_playerPointOfView->translate(glm::vec3(-KEYBOARD_CAMERA_CONTROL_SPEED,0,0));
            break;

            // right
        case 'l':
            m_playerPointOfView->translate(glm::vec3(KEYBOARD_CAMERA_CONTROL_SPEED,0,0));
            break;

            // Rotate right
        case 'u':
            m_playerPointOfView->rotate(KEYBOARD_CAMERA_CONTROL_SPEED, glm::vec3(0,1,0));
            break;

            // Rotate left
        case 'o':
            m_playerPointOfView->rotate(KEYBOARD_CAMERA_CONTROL_SPEED, glm::vec3(0,-1,0));
            break;

            // Rotate up
        case 'p':
            m_playerPointOfView->rotate(KEYBOARD_CAMERA_CONTROL_SPEED, glm::vec3(1,0,0));
            break;

            // rotate down
        case 'm':
            m_playerPointOfView->rotate(KEYBOARD_CAMERA_CONTROL_SPEED, glm::vec3(-1,0,0));
            break;

            // '0' key (not the numpad)
        case '0':
            // replace to origin
            m_playerPointOfView->resetPosition();
            break;
    }
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



void GameController::createMenu(){
    m_menu = std::make_shared<GraphicsEngine::Menu>(std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("assets/textures/overlaytest.png")));
    
}


void GameController::createCursor(){
    
    m_menucursor =  std::make_shared<GraphicsEngine::Object2D>(glm::vec2(-0.1, 0.1),
                                               glm::vec2(0.2, -0.2),
                                               std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("assets/textures/cursor.png")));
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
