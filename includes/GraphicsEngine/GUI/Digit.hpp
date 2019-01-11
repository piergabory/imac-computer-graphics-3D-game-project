/**
 * \file Digit.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Digit_h
#define Digit_h
#pragma once

#include "Object2D.hpp"
#include <vector>
#include <functional>


namespace GraphicsEngine {
    class Digit : public Object2D {
    private:
        char m_digit = 0;
        
        
        
    public:
        Digit(const glm::vec2 &position, const glm::vec2 &size, char digit);
        ~Digit();
        
        static void initializeDigit();
        
        void update(char newDigit);
        char current();
        
    };
}

#endif /* Digit_h */
