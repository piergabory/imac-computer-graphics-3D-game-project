/**
 * \file Menu.cpp
 */

#include "Menu.hpp"

namespace GraphicsEngine {
    Menu::Menu(std::shared_ptr<Texture> background) {
        m_overlay = std::make_shared<Object2D>(glm::vec2(-1,1), glm::vec2(2,-2), background);
            initializeButtons();
    };
    
    Menu::~Menu(){};
    
    std::vector< std::shared_ptr<Object2D> > Menu::elements(){
            std::vector< std::shared_ptr<Object2D> > elements = m_buttons;
            elements.push_back(m_overlay);
        return elements;
    };
    
    void Menu::add(std::function<void()> func){
        
        std::function<void(Button*, unsigned char)> click = [func](Button* target, unsigned char mouseButton) -> void {
            std::cout << "you clicked the resumebutton :" << target << std::endl;
            std::shared_ptr<Texture> clickTexture = std::make_shared<Texture>(LocalFilePath("assets/textures/test2.png"));
            target->texture(clickTexture);
            func();
        };
        
        m_buttons.push_back(std::make_shared<Button>(
                                                     glm::vec2(-0.5, 0.6),
                                                     glm::vec2(1, -0.3),
                                                     std::make_shared<Texture>(LocalFilePath("assets/textures/test.png")),
                                                     click
                                                     ));

    }
    
    void Menu::initializeButtons(){
        

        std::function <void()> quit = [](){
            std::cout << "quit game" << std::endl;
        };
        add(quit);
        
        std::function <void()> resume = [](){
            std::cout << "resume game" << std::endl;
        };
        add(resume);
        
    }
}
