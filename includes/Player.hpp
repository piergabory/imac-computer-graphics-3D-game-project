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
    Player(std::shared_ptr<GraphicsEngine::Object3D> obj): m_characterModel(obj) {}
    ~Player() {
        
    };


    inline std::shared_ptr<GraphicsEngine::Object3D> model() const {
        return m_characterModel;
    }


    void translate(const Direction &to) {
        char direction = static_cast<char>(to);
        if(abs(position + direction) <= 1) {
            position += direction;
            m_characterModel->translate(glm::vec3(direction * 3.0,0,0));
        }
    }
};

#endif
