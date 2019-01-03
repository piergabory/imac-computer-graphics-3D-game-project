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
    
    void Menu::add(std::function<void()> func, LocalFilePath texture_main, LocalFilePath texture_over){
        
        std::function<void(Button*, unsigned char)> click = [func, texture_over](Button* target, unsigned char mouseButton) -> void {
            std::cout << "you clicked the resumebutton :" << target << std::endl;
            std::shared_ptr<Texture> clickTexture = std::make_shared<Texture>(texture_over);
            target->texture(clickTexture);
            func();
        };
        
        double ypos = 0.6 - ((double)(m_buttons.size()) * (btn_height+btn_margin));
        
        m_buttons.push_back(std::make_shared<Button>(
                                                     glm::vec2(-(btn_width/2), ypos),
                                                     glm::vec2(btn_width, -btn_height),
                                                     std::make_shared<Texture>(texture_main),
                                                     click
                                                     ));

    }
    
    void Menu::initializeButtons(){
        

        std::function <void()> quit = [](){
            std::cout << "quit game" << std::endl;
        };
        add(quit, LocalFilePath("assets/textures/test2.png"),LocalFilePath("assets/textures/test.png") );
        
        std::function <void()> resume = [](){
            std::cout << "resume game" << std::endl;
        };
        add(resume,LocalFilePath("assets/textures/test.png"), LocalFilePath("assets/textures/test2.png"));
        
    }
}
