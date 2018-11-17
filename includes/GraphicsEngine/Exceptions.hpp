//
//  Exceptions.hpp
//  Project_Pasteque
//
//  Created by Pierre Gabory on 16/11/2018.
//

#ifndef Exceptions_h
#define Exceptions_h

#include <exception>
#include <iostream>
#include <string>

#include "Frameworks.hpp"

namespace GraphicsEngine
{
    
    class Exception : std::exception
    {
        
    private:
        std::string m_message;
        std::string m_info;
        
    public:
        const char* what() const throw() override;
        
        Exception(const char* message, const char* info);
        
        Exception(const char* message, GLuint identifier);
        
        ~Exception() override {}
    };
}

#endif /* Exceptions_h */
