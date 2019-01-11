/**
 * \file Menu.cpp
 */

#include "Menu.hpp"

namespace GraphicsEngine {
    Menu::Menu(std::shared_ptr<Texture> background) {
        m_elements.push_back(std::make_shared<Object2D>(glm::vec2(-1,1), glm::vec2(2,-2), background));
    };
    
    Menu::Menu(std::shared_ptr<Texture> background, double ypos) {
        m_elements.push_back(std::make_shared<Object2D>(glm::vec2(-1,1), glm::vec2(2,-2), background));
            btn_ypos = ypos;
    };
    
    Menu::~Menu(){};
    
    std::vector< std::shared_ptr<Object2D> > Menu::elements(){
        return m_elements;
    };
    
    void Menu::add(std::function<void()> func, LocalFilePath texture_main, LocalFilePath texture_hover){
        
        std::function<void(Button*, unsigned char)> click = [func](Button* target, unsigned char mouseButton) -> void {
            
            func();
        };
        
        double ypos = btn_ypos - ((double)(m_buttons.size()) * (btn_height+btn_margin));
        std::shared_ptr<Button> button = std::make_shared<Button>(
                                 glm::vec2(-(btn_width/2), ypos),
                                 glm::vec2(btn_width, -btn_height),
                                 std::make_shared<Texture>(texture_main),std::make_shared<Texture>(texture_hover),
                                 click
                                                                  );
        m_buttons.push_back(button);
        m_elements.push_back(button);

    }
    
    void Menu::next(){
        if (m_currentButton >= (int)m_buttons.size()-1){
            m_currentButton = (int)m_buttons.size()-1;
        } else {
            select();
            m_currentButton++;
            select();
        }
    }
    
    void Menu::previous(){
        if (m_currentButton <= 0){
            m_currentButton = 0;
        } else {
            select();
            m_currentButton--;
            select();
        }
    }
    
    
    void Menu::enter(){
        std::shared_ptr<Button> button =  m_buttons[m_currentButton];
        button ->click();
    }
    
    void Menu::select(){
        m_buttons[m_currentButton]->hover();
    };
    
    void Menu::initializeButtons(
                                 std::function <void()> resume,
                                 std::function <void()> save,
                                 std::function <void()> load,
                                 std::function <void()> quit
    ){
        

        add(resume,LocalFilePath("assets/textures/button_play1.png"), LocalFilePath("assets/textures/button_play2.png"));

        add(save, LocalFilePath("assets/textures/button_start1.png"),LocalFilePath("assets/textures/button_start2.png") );
        
        //LOAD
        //add(load, LocalFilePath("assets/textures/button_load1.png"),LocalFilePath("assets/textures/button_load2.png") );
        
        //QUIT
        add(quit, LocalFilePath("assets/textures/button_quit1.png"),LocalFilePath("assets/textures/button_quit2.png") );

        
    }
}
