#ifndef Game_hpp
#define Game_hpp

#include "Player.hpp"
#include "ImportedMesh.hpp"

class Game{
private:
    Player m_pPlayer;

    static std::shared_ptr<GraphicsEngine::Object3D> loadPlayerObject();

public:

    inline std::shared_ptr<GraphicsEngine::Object3D> playerModel() const {
        return m_pPlayer.model();
    }

    Game();
    ~Game();
};

#endif /* Game_hpp */
