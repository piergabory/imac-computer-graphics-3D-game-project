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
            unsigned int m_num;
            std::vector<int> m_digits;
        
        public:
            Number(unsigned int num);
            ~Number();
            void update(unsigned int newNum);
        
    };
}

#endif /* Number_h */
