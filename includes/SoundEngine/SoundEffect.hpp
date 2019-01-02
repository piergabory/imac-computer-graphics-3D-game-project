/**
 * \file Sample.hpp
 * \brief Sound shorter than 20 sec
 */
#ifndef SoundEffect_hpp
#define SoundEffect_hpp
#pragma once

#include "Sample.hpp"
#include "CommonStructs.hpp"
#include<SDL/SDL_mixer.h>
#include <string>

class SoundEffect : Sample{
    private:
    Mix_Chunk *m_chunk;

    public:
    ///\warning: the file should be .wave/.mp3
    ///\todo use GraphicsEngine::LocalFilePath
    SoundEffect(std::string const &path){
        m_filePath = path;
        m_chunk = Mix_LoadWAV(path.c_str());
        if(m_chunk=nullptr){
            throw std::exception();
        }
    }
    void free(){
        Mix_FreeChunk(m_chunk);
        m_chunk=nullptr;
    }

    void play(const int repeat =0) const{
        Mix_PlayChannel(-1,m_chunk,repeat);
    }

};
#endif