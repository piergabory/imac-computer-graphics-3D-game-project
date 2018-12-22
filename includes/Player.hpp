#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include <set>
#include <memory>
#include <cstddef>// nullptr
#include <glm/glm.hpp> //verctors
#include <ctime> //time in moovePlayer

#include "GraphicsEngine.hpp"
#include "EventObservers.hpp"
#include "Object.hpp"
#include "Animation.hpp"

enum class Direction: char {
    LEFT = -1,
    RIGHT = 1
};

enum class Position: char {
    LEFT = -1,
    MIDDLE = 0,
    RIGHT = 1
};

class Player : Events::KeyboardEventObserver {
private:
    std::shared_ptr<GraphicsEngine::Object3D> m_characterModel;   //eventuelement changer avec un MooveObject
    char position;
    
public:
    Player(std::shared_ptr<GraphicsEngine::Object3D> obj);
    ~Player() {};

    inline const std::shared_ptr<GraphicsEngine::Object3D>& model() const {
        return m_characterModel;
    }

    void translate(const Direction &to);
};

#endif
