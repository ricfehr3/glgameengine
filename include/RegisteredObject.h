#ifndef REGISTEREDOBJECT_H
#define REGISTEREDOBJECT_H

#include <string>
#include <exception>

#include <Logger.h>

class nonameexception : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Derived RegisteredObject name is empty";
    }
};

class RegisteredObject
{
public:
    std::string getName()
    {
        if(m_name.empty())
        {
            GLOG_ERROR("Derived RegisteredObject has empty name");
            throw nameex;
        }
        return m_name;
    }
    
protected:
    std::string m_name;
    nonameexception nameex;
};

#endif
