
/**
 * \file Digit.cpp
 */

#include "Digit.hpp"

namespace GraphicsEngine {
    
    std::vector < std::shared_ptr<Texture> > m_digitTextures;
    
    Digit::Digit(const glm::vec2 &position, const glm::vec2 &size, char digit) : Object2D(position, size, m_digitTextures[digit]), m_digit(digit){
        
    }
    
    Digit::~Digit(){}
    
    void Digit::update(char newDigit){
        m_digit = newDigit;
        texture(m_digitTextures[newDigit]);
    };
    
    void Digit::initializeDigit(){

        
    m_digitTextures.push_back(
                                  std::make_shared<Texture>(LocalFilePath("assets/textures/digit_0.png"))
                                  );
        
    m_digitTextures.push_back(
                                  std::make_shared<Texture>(LocalFilePath("assets/textures/digit_1.png"))
                                  );
    m_digitTextures.push_back(
                                  std::make_shared<Texture>(LocalFilePath("assets/textures/digit_2.png"))
                                  );
    
    m_digitTextures.push_back(
                                  std::make_shared<Texture>(LocalFilePath("assets/textures/digit_3.png"))
                                  );
        
    m_digitTextures.push_back(
                                  std::make_shared<Texture>(LocalFilePath("assets/textures/digit_4.png"))
                                  );
    
    m_digitTextures.push_back(
                                  std::make_shared<Texture>(LocalFilePath("assets/textures/digit_5.png"))
                                  );
    
    m_digitTextures.push_back(
                                  std::make_shared<Texture>(LocalFilePath("assets/textures/digit_6.png"))
                                  );
    m_digitTextures.push_back(
                                  std::make_shared<Texture>(LocalFilePath("assets/textures/digit_7.png"))
                                  );
        
    m_digitTextures.push_back(
                                  std::make_shared<Texture>(LocalFilePath("assets/textures/digit_8.png"))
                                  );
        
        
    m_digitTextures.push_back(
                                  std::make_shared<Texture>(LocalFilePath("assets/textures/digit_9.png"))
                                  );
    std::cout << "Nombre de chiffres chargées" << m_digitTextures.size() << std::endl;
    
    }
    
    char Digit::current(){
        return m_digit;
    };
    
};
