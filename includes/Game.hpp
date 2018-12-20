#ifndef Game_hpp
#define Game_hpp

#include "Player.hpp"
#include "ImportedMesh.hpp"

class Game{
private:
    Player m_pPlayer;

    static GraphicsEngine::Object3D loadPlayerObject();

public:
    Game();
    ~Game();
};

#endif /* Game_hpp */
