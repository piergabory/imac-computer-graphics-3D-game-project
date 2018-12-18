#ifndef Player_hpp
#deine Player_hpp

#include <iostream>
#include <set>
#include <memory>

#include "GraphicsEngine.hpp"
#include "EventObservers.hpp"

class Player : KeyboardEventObserver{
private:
  float x;
  float y;
  float z;
  float step;
  std::set<unsigned char>m_pressedKeys;
  MooveObjet cible; //obj joueur
public:
  //constucteur avec les var initiales à 0, prends en param la cible
  Player(const MooveObjet obj): cible(obj), x(0),y(0),z(0){}
  void keyDownHandler(unsigned char keycode) {
    m_pressedKeys.insert(keycode);
  }
  
  void moove(const bool tx, const bool ty, const bool tz) {
      /*Bouger dans la direction voulue puis faire un translate de la cible*/
      glm::vec3 vectorTransalte= glm::vec3(step*tx,step*ty,step*tz);
      cible.translate(vectorTransalte);
  }
};

#endif
