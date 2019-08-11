#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <string>
#include <RegisteredObject.h>

class MessageBase : public RegisteredObject
{
public:
    MessageBase();
    int getMessageArgs();
    bool matchFormat(std::string incomingMsg);
    
protected:
    std::string m_messageFormat;
    void setArgNumber();
    
    int m_argNumber;
};

#endif
