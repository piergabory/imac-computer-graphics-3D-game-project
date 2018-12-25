
#ifndef Exceptions_h
#define Exceptions_h

#include <exception>
#include <iostream>
#include <string>

#include "Frameworks.hpp"

// todo doc
namespace GraphicsEngine
{
    
    class InitialisationException : public std::exception
    {
        
    private:
        std::string m_message;
        std::string m_info;
        
    public:
        
        const char* what() const throw() override;
        
        InitialisationException(const char* message, const char* info);
        
        InitialisationException(const char* message, GLuint identifier);
        
        InitialisationException() = default;
        
        ~InitialisationException() throw() {}
    };
}


class SaveLoaderException : public std::exception
{

private:
    std::string m_message;
    std::string m_info;

public:

    const char* what() const throw() override;

    SaveLoaderException(const char* message, const char* info);

    SaveLoaderException() = default;

    ~SaveLoaderException() throw() {}
};

#endif /* Exceptions_h */
