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

    class Menu : public Object2D {
        public :
            ///\brief  constructor
            Menu(std::shared_ptr<Texture> sprite);
            ~Menu();
            
        
        private :
            std::vector< std::shared_ptr<Button> > boutons;
    };
}



#endif /* Menu_h */
