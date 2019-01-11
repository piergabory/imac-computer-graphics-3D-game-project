/**
 * \file Number.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Number_h
#define Number_h
#pragma once


#include "Digit.hpp"

namespace GraphicsEngine {
    class Number {
        private:
            std::vector< std::shared_ptr<Digit> > m_digitsObjects;
            std::vector< std::shared_ptr<Object2D> > m_elements;
        
            unsigned int m_num;
            std::vector<int> m_digits;
        
            double m_posx= -0.2;
            double m_posy= -0.8;
        
            double m_width= 0.4;
            double m_height= 0.2;
        
            void initializeDigitsObjects();
        
        public:
            Number(unsigned int num);
            ~Number();
            void update(unsigned int newNum);
            std::vector< std::shared_ptr<Object2D> > elements();
        
    };
}

#endif /* Number_h */
