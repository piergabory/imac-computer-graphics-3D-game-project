//
//  Exceptions.cpp
//  product
//
//  Created by Pierre Gabory on 16/11/2018.
//

#include "Exceptions.hpp"

namespace GraphicsEngine
{
    InitialisationException::InitialisationException(const char* message, const char* info) :
        m_message(message), m_info(info)
    {}
    
    
    
    InitialisationException::InitialisationException(const char* message, GLuint identifier) :
        m_message(message)
    {
        GLint logCharacterLength;
        glGetProgramiv(identifier, GL_INFO_LOG_LENGTH, &logCharacterLength);
        char* text = new char[logCharacterLength];
        glGetProgramInfoLog(identifier, logCharacterLength, 0, text);
        
        m_info = text;
        delete [] text;
    }
    
    
    
    const char* InitialisationException::what() const throw()
    {
        std::string ret;
        ret += "\n/!\\ GRAPHICS ENGINE EXCEPTION :";
        ret += m_message;
        ret += "\n";
        ret += m_info;
        ret += "\n";
        return ret.c_str();
    }
}
