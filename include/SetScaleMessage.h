#ifndef SETSCALEMESSAGE_H
#define SETSCALEMESSAGE_H

#include <MessageBase.h>

class SetScaleMessage : public MessageBase
{
public:
    SetScaleMessage();
    std::string processMessage(std::string incomingMsg);
};

#endif