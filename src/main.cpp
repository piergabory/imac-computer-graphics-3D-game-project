
#include "GameController.hpp"

int main(int argc, const char * argv[]) {
    GraphicsEngine::LocalFilePath::setLocation(*argv);
    GameController::instance()->setup();
    while (GameController::instance()->loop());
    return 0;
}
