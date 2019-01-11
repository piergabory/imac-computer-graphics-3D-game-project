
/**
 * \file Number.cpp
 */

#include "Number.hpp"

namespace GraphicsEngine {
    Number::Number(unsigned int num) : m_num(num) {
        update(num);
    }
    
    Number::~Number(){}
    
    void Number::update(unsigned int newNum){
        m_num = newNum;
        m_digits.clear();
        
        while(newNum){
            m_digits.push_back(newNum%10);
            newNum /= 10;
        }
        
        std::reverse(m_digits.begin(),m_digits.end());
        std::cout << "Chiffres mis à jour : ";
        for (int i= 0; i < m_digits.size(); i++){
            std::cout << m_digits[i] << " ";
        }
        std::cout << std::endl;
    }
    
    
}
