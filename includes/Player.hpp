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

class Player : Events::KeyboardEventObserver {
private:
    /*
     * m_characterModel : mesh of the Player
     * m_speed : in how many frame the player has to do his annimation (side to side, half of a jump)
     * m_position : the current posion of the player
     */
    std::shared_ptr<GraphicsEngine::Object3D> m_characterModel;   //eventuelement changer avec un MooveObject
    int m_speed;
    glm::vec3 m_position;
    
public:
    /**
     * \brief constucteur avec les var initiales à 0, prends en param la cible
     * @param[in] obj L'objet qui servira de mesh pour le joueur
     * @param[in] speed distance qui sera rajouté aux coordonnées à chaque fois qu'une touche sera pressée
     */
    Player(std::shared_ptr<GraphicsEngine::Object3D> obj, const int speed = 1, const glm::vec3 &position = glm::vec3(0.f)): m_characterModel(obj), m_speed(speed), m_position(position){
        //lever les erreurs
        if(speed<0){
            throw std::invalid_argument( "Player speed can not be negative.");
        }
        //subscribe to keyboard listener
        Events::Manager::instance()->subscribe(this);
        std::cout << "New player in:\n\t- x : "<<m_position[0]<<"\n\t- y : "<<m_position[1]<<"\n\t- z : "<<m_position[2]<< std::endl;
    }
    
    inline std::shared_ptr<GraphicsEngine::Object3D> model() const {
        return m_characterModel;
    }


    /**
     * \brief method called by the KeyboardEventObserver
     * @param[in] pressedKeys set of the keys currently pressed
     */
    virtual void keyPressHandler( const std::set<unsigned char> pressedKeys){
        for(std::set<unsigned char>::iterator it=pressedKeys.begin(); it!=pressedKeys.end(); ++it){
            switch (*it) {
                case 'R':
                    std::cout << "Player: ^ (UP)" << '\n';
                    //TODO implement jump
                    break;
                case 'O':
                    std::cout << "Player:-->" << '\n';
                    break;
                case 'Q':
                    std::cout << "Player: v (DOWN)" << '\n';
                    break;
                case 'P':
                    std::cout << "Player: <--" << '\n';
                    break;
                    //No default because the player isn't supposed to react to other key
            }
        }
    }
    
    //function called in each loop
    //  void moovePlayer(unsigned char direction, std::time &startTime) {
    //    /* TODO: en fonction de la direction
    //            peutètre faire d'autres fonction pour le déplacemennt latéral et le saut
    //    */
    //  }
};

#endif
