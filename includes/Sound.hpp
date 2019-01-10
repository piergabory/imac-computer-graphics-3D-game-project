/**
 * \file Sound.hpp
 * \brief file tha play sound (lazy SoundEngine)
 */
#ifndef Sound_hpp
#define Sound_hpp
#pragma once

#include <SDL2/SDL.h>
#include <iostream> 
#include "EventManager.hpp"


class Sound : Events::QuitEventObserver{
    private:
        SDL_AudioSpec m_wavSpec;
        Uint32 m_wavLength;
        Uint8 *m_wavBuffer;
        SDL_AudioDeviceID m_deviceId;

    public:
    
    Sound();
    /**
     * \brief free the musique when the game close
     */
    void quitEventHandler(){
        SDL_CloseAudioDevice(m_deviceId);
        SDL_FreeWAV(m_wavBuffer);
    };
    /**
     * \brief play musique background
     * @param path path to the musique look like this: assets/Musiques/file.wav
     */
    void playWAVfile(const char* path){
        //loadFile
        if(SDL_LoadWAV(path, &m_wavSpec, &m_wavBuffer, &m_wavLength)==NULL){
            std::cerr<<"Could not open the file: "<<path<<std::endl;
        }
        //open audio device
        m_deviceId = SDL_OpenAudioDevice(nullptr,0,&m_wavSpec,nullptr,0);
        //play audio
        SDL_QueueAudio(m_deviceId, m_wavBuffer,m_wavLength);
        SDL_PauseAudioDevice(m_deviceId,0);
    };
};
#endif
