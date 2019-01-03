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
    
    void Menu::initializeButtons(){
        
        std::function<void(GraphicsEngine::Button*, unsigned char)> click = [](GraphicsEngine::Button* target, unsigned char mouseButton) -> void {
            std::cout << "you clicked the resumebutton :" << target << std::endl;
            std::shared_ptr<GraphicsEngine::Texture> clickTexture = std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("assets/textures/test2.png"));
            target->texture(clickTexture);
        };
        
        m_buttons.push_back(std::make_shared<GraphicsEngine::Button>(
                                                                  glm::vec2(-0.5, 0.6),
                                                                  glm::vec2(1, -0.3),
                                                                  std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("assets/textures/test.png")),
                                                                  click
                                                                     ));
        
        
        
        
        m_buttons.push_back (std::make_shared<GraphicsEngine::Button>(
                                                                glm::vec2(-0.5, 0.2),
                                                                glm::vec2(1, -0.3),
                                                                std::make_shared<GraphicsEngine::Texture>(GraphicsEngine::LocalFilePath("assets/textures/test.png")),
                                                                click
                                                                ));
    }
}
