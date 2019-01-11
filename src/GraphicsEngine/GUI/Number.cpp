
/**
 * \file Number.cpp
 */

#include "Number.hpp"
#include "Digit.hpp"

namespace GraphicsEngine {
    Number::Number(unsigned int num) : m_num(num) {
        update(num);
        initializeDigitsObjects();
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

    }
    
    void Number::initializeDigitsObjects(){
        std::cout << "Creation des chiffres : ";
        for (int i=0 ; i < m_digits.size(); i++){
            double x = m_posx+(m_width/m_digits.size())*i;
            
            std::shared_ptr<Digit> currentDigit = std::make_shared<Digit>(glm::vec2(x,m_posy),glm::vec2(m_width/m_digits.size(),-m_height), m_digits[i]);
            
            m_digitsObjects.push_back(currentDigit);
            m_elements.push_back(currentDigit);
            
            std::cout << m_digits[i] << " ";
        }
        std::cout << std::endl;
    }
    
    std::vector< std::shared_ptr<Object2D> > Number::elements(){
        return m_elements;
    }
    
    
}
