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
        
            ///\brief  constructor
            Menu(std::shared_ptr<Texture> sprite);
            ~Menu();
        
            
        
        private :
            std::vector< std::shared_ptr<Object2D> > m_buttons;
            std::shared_ptr<Object2D> m_overlay;
        
            double btn_height = 0.3;
            double btn_width = 1.0;
            double btn_margin = 0.1;
        
            void initializeButtons();
           
    };
}



#endif /* Menu_h */
