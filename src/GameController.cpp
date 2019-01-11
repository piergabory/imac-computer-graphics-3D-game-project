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
    m_playerPointOfView->switchMode(GraphicsEngine::CameraControl::TURNTABLE);
    m_playerPointOfView->place(glm::vec3(0,4,8));
    std::unique_ptr<GraphicsEngine::Scene> scene(new GraphicsEngine::Scene(m_playerPointOfView));
    GraphicsEngine::Controller::instance()->loadScene(scene);

    //Musique
    ///\todo file withe the rigth wav
    m_soundManageur.playWAVfile("assets/Musiques/43mozarts15a.wav");

    // create objects
    m_skybox = createSkyBox();
    m_chunk = createChunk();
    createNumber();
    toggleMenu();


    // skybox max scale before clipping out of far-field
    m_skybox->scale(glm::vec3(30.f));


    // adds objects in the scene
    GraphicsEngine::Controller::instance()->activeScene()->add(m_currentGame->playerModel());
    GraphicsEngine::Controller::instance()->activeScene()->add(m_currentGame->enemyModel());
    GraphicsEngine::Controller::instance()->activeScene()->add(m_skybox);
    GraphicsEngine::Controller::instance()->activeGUI()->add(m_digit);
    
}



void GameController::setup() {
    //m_framecount == 0;
    
    // initialize framworks and windows
    GraphicsEngine::Controller::instance()->setup();
    GraphicsEngine::Controller::instance()->printInfos();

    m_currentGame = std::unique_ptr<GameModel::Game>(new GameModel::Game);
    m_currentGame->onPlayerDeath([=](void) -> void {
        // wait for all animations to terminate
        if (GraphicsEngine::Animation::activeCount() > 0) return;
        m_isPaused = true;
        /// \todo reinit the game
    });

    // create scene
    initializeScene();

    for (std::shared_ptr<GraphicsEngine::Object3D> object : m_currentGame->terrain().preloadInitialChunks()) {
        GraphicsEngine::Controller::instance()->activeScene()->add(object);
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
    if (m_menu == nullptr || m_framecount == 0) {
        if(m_framecount % 100 == 0) loadNewChunks(100);
        std::set<std::shared_ptr<GraphicsEngine::Object3D>> newObjects = m_currentGame->update();
        for(std::shared_ptr<GraphicsEngine::Object3D> object : newObjects) {
            GraphicsEngine::Controller::instance()->activeScene()->add(object);
        }
        GraphicsEngine::Animation::updateAnimations();
    }

    // start new render cycle
    GraphicsEngine::Controller::instance()->render();

    // fetches new events
    Events::Manager::instance()->pollEvents();
    m_framecount ++;

    // calculate the time spent since the start of the game loop
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < 1000 / FRAMERATE) {
        // wait a while before the next frame, in order to keep a consistent framerate.
        SDL_Delay(1000 / FRAMERATE - elapsedTime);
    }
    return m_isRunning;
}



void GameController::loadNewChunks(unsigned int chunkCount) {
    for (unsigned int i = 0; i < chunkCount; ++i) {
        GameModel::Chunk* chunk;
        std::shared_ptr<GraphicsEngine::Animatable> cameraAnimatable(m_playerPointOfView);
        std::shared_ptr<GraphicsEngine::Animatable> playerAnimatable(m_currentGame->playerModel());

        if (i % 40 == 0) {
            chunk = new GameModel::TurningChunk(GameModel::TurnDirection::LEFT, playerAnimatable, cameraAnimatable);
        } else if(i % 50 == 0) {
            chunk = new GameModel::TurningChunk(GameModel::TurnDirection::RIGHT, playerAnimatable, cameraAnimatable);
        } else if(i % 15 == 0) {
            chunk = new GameModel::Chunk(new GameModel::Coin(),
                                         new GameModel::PowerUp(),
                                         new GameModel::Wall(playerAnimatable, cameraAnimatable));
        } else if(i % 10 == 0) {
            chunk = new GameModel::Chunk(new GameModel::Jump(playerAnimatable, cameraAnimatable),
                                         new GameModel::Entity(),
                                         new GameModel::Slide(playerAnimatable, cameraAnimatable));
        } else {
            chunk = new GameModel::Chunk();
        }

        m_currentGame->loadInChunkBuffer(chunk);
//        for(std::shared_ptr<GraphicsEngine::Object3D> object : chunk->objects()) {
//            GraphicsEngine::Controller::instance()->activeScene()->add(object);
//        }
    }
}



void GameController::quitEventHandler() {
    m_isRunning = false;
    GraphicsEngine::Controller::instance()->close();
}


// a déolacer dans l'EventManager
void GameController::keyRealeaseHandler(const unsigned char keycode) {
    if (m_menu){
        switch (keycode) {
                case SDLK_RETURN:
                    m_menu->enter();
                    break;
                
                // escape key
                case SDLK_ESCAPE:
                    SDL_CaptureMouse(SDL_TRUE);
                    SDL_ShowCursor(SDL_DISABLE);
                    toggleMenu();
                    break;
                
                case SDLK_z:
                    m_menu->previous();
                    break;
                
            case SDLK_q:
                    m_menu->previous();
                    break;
                
                case SDLK_d:
                    m_menu->next();
                    break;
               
            case SDLK_s:
                    m_menu->next();
                    break;
        }
    } else {
        // check if debug shortcuts is activated (CTRL-SHIFT):
        switch (keycode) {
                // escape key
            case SDLK_ESCAPE:
                SDL_CaptureMouse(SDL_FALSE);
                SDL_ShowCursor(SDL_ENABLE);
                toggleMenu();
                break;

            case SDLK_z: m_currentGame->callInput(GameModel::Controls::UP); break;
            case SDLK_q: m_currentGame->callInput(GameModel::Controls::LEFT); break;
            case SDLK_d: m_currentGame->callInput(GameModel::Controls::RIGHT); break;
            case SDLK_s: m_currentGame->callInput(GameModel::Controls::DOWN); break;

            case SDLK_c:
                m_cameraBehavior = static_cast<CameraBehaviors>(((int)m_cameraBehavior + 1) % 4);
                if (m_cameraBehavior == CameraBehaviors::THIRD_PERSON) {
                    m_playerPointOfView->switchMode(GraphicsEngine::CameraControl::TURNTABLE);
                    m_playerPointOfView->place(glm::vec3(0,4,8));
                } else {
                    m_playerPointOfView->switchMode(GraphicsEngine::CameraControl::FLY);
                    m_playerPointOfView->place(glm::vec3(0,0,1));
                    m_playerPointOfView->rotate(-10, glm::vec3(1,0,0));
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


            case SDLK_p:
                // freeze
                m_isPaused = !m_isPaused;
                break;
        }
    }
};


void GameController::keyPressHandler(const std::set<unsigned char> &pressedKeys) {
    for (unsigned char key : pressedKeys) {
        cameraMoves(key);
    }
}



void GameController::mouseMoveHandler(float relativeXMovement,float relativeYMovement) {
    if (m_cameraBehavior != CameraBehaviors::FREE) return;
    const float MOUSEMOVE_SCALING = 0.006;
    m_playerPointOfView->rotate(relativeXMovement * MOUSEMOVE_SCALING, glm::vec3(0,-1,0));
    m_playerPointOfView->rotate(relativeYMovement * MOUSEMOVE_SCALING, glm::vec3(1,0,0));
}


void GameController::mouseWheelHandler(float deltaX, float deltaY) {
    if (m_cameraBehavior != CameraBehaviors::FREE) return;
    const float MOUSEWHEEL_SCALING = 0.1;
    m_playerPointOfView->translate(glm::vec3(MOUSEWHEEL_SCALING * deltaX, 0, MOUSEWHEEL_SCALING * deltaY));
}


void GameController::mouseReleaseHandler(const unsigned char button) {
    SDL_CaptureMouse(SDL_TRUE);
    SDL_ShowCursor(SDL_ENABLE); ///TODO - put back to disable
}


void GameController::cameraMoves(const unsigned char key) {
    if (m_cameraBehavior != CameraBehaviors::FREE) return;
    const float KEYBOARD_CAMERA_CONTROL_SPEED = 0.1;
    switch(key) {
            // Up
        case SDLK_i:
            m_playerPointOfView->translate(glm::vec3(0,-KEYBOARD_CAMERA_CONTROL_SPEED,0));
            break;

            // Down
        case SDLK_k:
            m_playerPointOfView->translate(glm::vec3(0,KEYBOARD_CAMERA_CONTROL_SPEED,0));
            break;

            // left
        case SDLK_j:
            m_playerPointOfView->translate(glm::vec3(-KEYBOARD_CAMERA_CONTROL_SPEED,0,0));
            break;

            // right
        case SDLK_l:
            m_playerPointOfView->translate(glm::vec3(KEYBOARD_CAMERA_CONTROL_SPEED,0,0));
            break;

            // Rotate right
        case SDLK_u:
            m_playerPointOfView->rotate(KEYBOARD_CAMERA_CONTROL_SPEED, glm::vec3(0,1,0));
            break;

            // Rotate left
        case SDLK_o:
            m_playerPointOfView->rotate(KEYBOARD_CAMERA_CONTROL_SPEED, glm::vec3(0,-1,0));
            break;

            // Rotate up
        case SDLK_p:
            m_playerPointOfView->rotate(KEYBOARD_CAMERA_CONTROL_SPEED, glm::vec3(1,0,0));
            break;

            // rotate down
        case SDLK_m:
            m_playerPointOfView->rotate(KEYBOARD_CAMERA_CONTROL_SPEED, glm::vec3(-1,0,0));
            break;

            // '0' key 
        case SDLK_0:
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
    GraphicsEngine::LocalFilePath chunkmesh("assets/models/skybox.obj");
    GraphicsEngine::LocalFilePath chunktex("assets/textures/skybox.png");
    GraphicsEngine::LocalFilePath chunkvs("shaders/perspective.vs.glsl");
    GraphicsEngine::LocalFilePath chunkfs("shaders/flatTexture.fs.glsl");
    return createObject3D(chunkmesh, chunktex, chunkvs, chunkfs);
}


// make chunk
std::shared_ptr<GraphicsEngine::Object3D> GameController::createChunk() {
    GraphicsEngine::LocalFilePath chunkmesh("assets/models/legacy/cube.obj");
    GraphicsEngine::LocalFilePath chunktex("assets/textures/legacy/cubemap_a.png");
    GraphicsEngine::LocalFilePath chunkvs("shaders/perspective.vs.glsl");
    GraphicsEngine::LocalFilePath chunkfs("shaders/lighting.fs.glsl");

    return createObject3D(chunkmesh, chunktex, chunkvs, chunkfs);
}



void GameController::createMenu(){
    m_menu.reset(new GraphicsEngine::Menu(std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("assets/textures/overlay-menu.png"))));
}

void GameController::toggleMenu(){
    if (!m_menu) {
        createMenu();
        m_menu->initializeButtons(
              [=]() -> void { /* resume */ toggleMenu(); },
                                  [=]() -> void {
                                      m_isRunning = false;
                                      system(("\"" + GraphicsEngine::LocalFilePath("bin/product") + "\"").c_str());
                                  },
              [=]() -> void { /* load */ },
              [=]() -> void { /* quit */ m_isRunning = false; }
          );
        m_menu->select();
        GraphicsEngine::Controller::instance()->activeGUI()->add(m_menu->elements());
    } else {
        m_menu.reset(nullptr);
    }
}




// singleton

GameController* GameController::s_controllerInstance = nullptr;

GameController* GameController::instance() {
    if (s_controllerInstance == nullptr)
        s_controllerInstance = new GameController();
    return s_controllerInstance;
}


void GameController::createNumber(){
    GraphicsEngine::Digit::initializeDigit();
    m_digit = std::make_shared<GraphicsEngine::Digit>(glm::vec2(-1,1),glm::vec2(0.5,-0.5),std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("assets/textures/digit_0.png")));
 
    char number = 3;
    m_digit->update(number);
    
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
