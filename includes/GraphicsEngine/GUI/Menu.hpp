/**
 * \file Menu.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Menu_h
#define Menu_h
#pragma once

#include <memory>
#include <vector>
#include <algorithm> //for clamp
#include "Button.hpp"

namespace GraphicsEngine {
    /**
     * MENU CLASS
     *
     * \brief Extension to Object2D.
     * \version 0.1
     *
     */

    class Menu {
        public :
            std::vector< std::shared_ptr<Object2D> > elements();
        
            void add(std::function<void()> func, LocalFilePath texture_main, LocalFilePath texture_over); ///TODO check if can be optimized (reference)
        
            void next();
            void previous();
        
            void enter();

            void initializeButtons(
                                   std::function <void()> resume,
                                   std::function <void()> save,
                                   std::function <void()> load,
                                   std::function <void()> quit
                                   );
            void select();
        
            ///\brief  constructor
            Menu(std::shared_ptr<Texture> sprite);
            ~Menu();

            
        
            
        
        private :
            std::vector< std::shared_ptr<Button> > m_buttons;
            std::vector< std::shared_ptr<Object2D> > m_elements;
            int m_currentButton = 0;
        
            double btn_height = 0.33;
            double btn_width = 1.0;
            double btn_margin = 0.05;
        

    };
}



#endif /* Menu_h */
