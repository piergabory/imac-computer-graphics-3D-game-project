/**
 * \file Sample.hpp
 * \brief File that contain sound methodes
 */
#ifndef Sample_hpp
#define Sample_hpp
#pragma once

#include<SDL/SDL_mixer.h>
#include <string>

/// classe viruelle pure
class Sample{
    protected:
    std::string m_filePath;
    bool m_loop;

    public:
    virtual void play(const int repeat =0) const;
    virtual void free();
    virtual void stop();
    virtual void pause();
    virtual void toggleLoop(){
        if(m_loop){
            m_loop = false;
        }else{
            m_loop = true;
        }
    }

};

#endif