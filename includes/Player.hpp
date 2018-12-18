#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include <set>
#include <memory>
#include <cstddef>// nullptr
#include <glm/glm.hpp> //vercteurs

#include "GraphicsEngine.hpp"
#include "EventObservers.hpp"
#include "Object.hpp"

class Player : KeyboardEventObserver {
private:
  //eventuelement changer avec un MooveObject
  GraphicsEngine::Object m_characterModel; //mesh du joueur
  float m_speed;
  glm::vec3 m_position;

public:
  /**
  * \brief constucteur avec les var initiales à 0, prends en param la cible
  * @param[in] obj L'objet qui servira de mesh pour le joueur
  * @param[in] speed distance qui sera rajouté aux coordonnées à chaque fois qu'une touche sera pressée
  */
  Player(const GraphicsEngine::Object &obj, const float speed, const glm::vec3 &position = glm::vec3(0.f)): m_characterModel(obj), m_speed(speed), m_position(position){
    //lever les erreurs
    if(speed<0){
       throw std::invalid_argument( "Player speed can not be negativ.");
    }
    //subscribe au keyboard listener
    GraphicsEngine::EventManager::instance()->subscribe(this);
    std::cout << "joueur créé en position:\n\t- x : "<<m_position[0]<<"\n\t- y : "<<m_position[1]<<"\n\t- z : "<<m_position[2]<< std::endl;
  }

  //method de l'observeurs --> handles a set of keys
  virtual void keyPressHandler(std::set<unsigned char> pressedKeys){
    //faire des truc quand on apuis sur une touche
    std::cout << "Conenu pressedKeys de joueur" << '\n';
    for(std::set<unsigned char>::iterator it=pressedKeys.begin(); it!=pressedKeys.end(); ++it){
      std::cout << " " <<*it;
    }
    std::cout << '\n';
  }

  /*
  void moove(const bool tx, const bool ty, const bool tz) {
      //Bouger dans la direction voulue puis faire un translate de la cible
      glm::vec3 vectorTransalte= glm::vec3(step*tx,step*ty,step*tz);
      cible.translate(vectorTransalte);
  }*/
};

#endif
