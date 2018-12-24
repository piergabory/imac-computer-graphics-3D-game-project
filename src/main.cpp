
#include "GameController.hpp"
#include <string>

int main(int argc, const char * argv[]) {
    
    
    LocalFilePath::setLocation(*argv);
    GameController::instance()->setup();
        
    while (GameController::instance()->loop());
    
    return 0;
}
