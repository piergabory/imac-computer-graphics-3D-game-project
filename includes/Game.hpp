#ifndef Game_hpp
#define Game_hpp

#include "Player.hpp"
#include "ImportedMesh.hpp"

enum class Controls : unsigned char {
    LEFT, RIGHT, UP, DOWN
};

class Game{
private:
    Player m_pPlayer;

    static std::shared_ptr<GraphicsEngine::Object3D> loadPlayerObject();

    GraphicsEngine::Animation m_moveToLeftPath;
    GraphicsEngine::Animation m_moveToMiddlePath;
    GraphicsEngine::Animation m_moveToRightPath;
    GraphicsEngine::Animation m_playerJump;

public:

    inline std::shared_ptr<GraphicsEngine::Object3D> playerModel() const {
        return m_pPlayer.model();
    }

    void callInput(Controls control) {
        switch(control) {
            case Controls::LEFT:
                m_moveToLeftPath.begin();
                break;

            case Controls::RIGHT:
                m_moveToRightPath.begin();
                break;

            case Controls::UP:
                m_playerJump.begin();
                break;

            case Controls::DOWN:
                m_moveToMiddlePath.begin();
                break;

        }
    }

    Game();
    ~Game();
};

#endif /* Game_hpp */
