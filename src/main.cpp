
#include "GameController.hpp"
#include "Model.hpp"
#include <string>

int main(int argc, const char * argv[]) {
    //test
    GraphicsEngine::Model model("/Users/djaydnova/Developer/IMAC2_CG_CPP_Game_Project/assets/monkey1.obj",false);
    
    
    
    GraphicsEngine::LocalFilePath::setLocation(*argv);
    GameController::instance()->setup();
    while (GameController::instance()->loop());
    
    return 0;
}
