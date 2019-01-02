/**
 * \file SoundEngine.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef SoundEngine_hpp
#define SoundEngine_hpp
#pragma once

#include<SDL/SDL_mixer.h>
#include "Musique.hpp"
#include "SoundEffect.hpp"

namespace SoundEngine{

    class Controller{
        private:
            // singleton instance
            static Controller* s_controllerInstance;
            //sortie audio
            SDL_AudioSpec m_audioOut;
            std::vector<Musique> m_musiques;
            std::vector<SoundEffect> m_soundEffects;
            
            //singleton constructor
            Controller(){}

            void initializeSDL();
            void quit();
        public:

    };
}
#endif