#ifndef Sound_hpp
#define Sound_hpp
#pragma once

#include <SDL2/SDL.h>
#include "EventManager.hpp"
#include "CommonStructs.hpp"

class Sound : Events::QuitEventObserver{
    private:
        SDL_AudioSpec m_wavSpec;
        Uint32 m_wavLength;
        Uint8 *m_wavBuffer;
        SDL_AudioDeviceID m_deviceId;

    public:
    
    Sound();

    void quitEventHandler(){
        SDL_CloseAudioDevice(m_deviceId);
        SDL_FreeWAV(m_wavBuffer);
    };
    void playWAVfile(GraphicsEngine::LocalFilePath path){
        //loadFile
        SDL_LoadWAV(path.c_str(), &m_wavSpec, &m_wavBuffer, &m_wavLength);
        //open audio device
        m_deviceId = SDL_OpenAudioDevice(nullptr,0,&m_wavSpec,nullptr,0);
        //play audio
        // int success=
        SDL_QueueAudio(m_deviceId, m_wavBuffer,m_wavLength);
        SDL_PauseAudioDevice(m_deviceId,0);
    };
};
#endif
