/**
 * \file Sample.hpp
 * \brief Sound longeur than 20 sec
 */
#ifndef Musique_hpp
#define Musique_hpp
#pragma once

#include "Sample.hpp"
#include "CommonStructs.hpp"
#include<SDL/SDL_mixer.h>
#include <string>

class Musique : Sample{
    private:
    Mix_Music *m_musique;
    public:
    ///\warning: the file should be .wave/.midi/.mp3
    ///\todo use GraphicsEngine::LocalFilePath
    Musique(std::string const &path){
        m_filePath = path;
        m_musique = Mix_LoadMUS(path.c_str());
        if(m_musique==nullptr){
            throw std::exception();
        }
    }

    void free(){
        Mix_FreeMusic(m_musique);
        m_musique=nullptr;
    }
    void play(const int repeat =0) const{
        Mix_PlayMusic(m_musique,repeat);
    }
    void stop()const{
        Mix_HaltMusic();
    }
    void pause()const{
        if(!Mix_PlayingMusic()){
            //if not playing musique
            if(m_loop){
                Mix_PlayMusic(m_musique,-1);
            }
            else{
                Mix_PlayMusic(m_musique,0);
            }
        }else if(Mix_PausedMusic){
            Mix_ResumeMusic();
        }else{
            Mix_PauseMusic();
        };
    }

};
#endif