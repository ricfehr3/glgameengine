#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <string>
#include <regex>

#include <RegisteredObject.h>

class MessageBase : public RegisteredObject
{
public:
    MessageBase();
    bool matchFormat(std::string incomingMsg);
    virtual std::string processMessage(std::string incomingMsg) = 0;
    bool checkExistGameObject(std::string name);
    
protected:
    std::regex m_messageFormat;
};

#endif
