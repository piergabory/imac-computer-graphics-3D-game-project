Comment utiliser Doxygen: exemple type C++ d'une classe
(tout est optionnel)
Comment générer la doc:
-commande "doxywizard"

/**
*
* \file Rectangle.cpp (optionnel)
* \brief Courte description (sur une ligne si possible)
* \author Jon Doe (liste des auteurs)
* \version 0.1
* \date 17/12/18
*
* Longue description
* qui peut être sur plusieurs lignes.
*
*/

class Rectangle{
private:
  int l; ///< Longueur
  int h; ///< Hauteur

public:
  /// Cette methode fait qqch
  void doSomething();

  /**
  * Cette methode fait
  * autre chose!
  */
  void doSomethingElse();

  /**
  * \brief description
  * @param a un int qui sert a qqch
  *
  *description très longue...
  */
  void usefulMethode(int a);
}
