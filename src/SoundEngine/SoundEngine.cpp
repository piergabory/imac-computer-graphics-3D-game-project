/**
 * \file SoundEngine.cpp
 */

#include "SoundEngine.hpp"
#include<SDL>
#include<SDL/SDL_mixer.h>


namespace SoundEngine{
    //singleton instance difinition
    Controller* Controller::s_controllerInstance= nullptr;

    //singleton instance getter
    Controller* Controller::instance(){
        if(Controller::s_controllerInstance==nullptr)
        Controller::s_controllerInstance = new Controller();

        return Controller::s_controllerInstance;
    }


    //set the SDL Framework
    void Controller::initializeSDL(){
        public:
        //init and check
        if(-1 == SDL_Init(SDL_INIT_AUDIO)){
            throw InitialisationException("Failed to initialise SDL.", SDL_GetError());
        }
        /**
         * Mix_OpenAudio parameters
         * frequency of the oaudio
         * audio type
         * mono or stero (1 or 2)
         * sample size (play with this if you have lag)
        */
        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
            throw Mix_GetError();
        }
    }
    void quit(){
        for(std::vector<Musique>::iterator i = m_musiques.begin(); i!=m_musiques.end(); ++i){
            i.free();
        }
        for(std::vector<SoundEffect>::iterator i = m_soundEffects.begin(); i!=m_soundEffects.end(); i++){
            i.free();
        }
        Mix_Quit();
    }
}