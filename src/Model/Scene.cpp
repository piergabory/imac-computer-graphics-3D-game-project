//#include "Scene.hpp"
//
//#include <iostream>
//#include <vector>
//
//namespace IMAC2_CG
//{
//    void Scene::tour() 
//    {
//      while (m_player.life() != 0) {
//        std::cout << "\n **************************************** \n" << std::endl;
//        // Display of the next step 
//        std::cout << "| "
//        << m_terrain[0].entityAt(Position::LEFT)->display() << " | " 
//        << m_terrain[0].entityAt(Position::MIDDLE)->display() << " | "
//        << m_terrain[0].entityAt(Position::RIGHT)->display() << " | "
//        << std::endl;
//        
//        // Display life and score of the player 
//        std::cout << "\n" << std::endl;
//        std::cout << "Life :" <<  m_player.life() <<  std::endl;
//        std::cout << "Score :" <<  m_player.score() <<  std::endl;
//        
//        // Move and action of the player 
//        m_player.setPosition();
//        m_player.setStatus();
//        
//        // interacting with the obstacle or the bonus 
//        Position activeposition = m_player.position();
//        m_terrain.front().entityAt(activeposition)->action(m_player);
//        
//        // Reset player's status on running after passing the step 
//        m_player.resetStatus();
//        
//        // Erasing first step to go to the next one
//        m_terrain.erase(m_terrain.begin()); 
//        }
//    }   
//}
