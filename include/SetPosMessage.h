#ifndef SETPOSMESSAGE_H
#define SETPOSMESSAGE_H

#include <MessageBase.h>

class SetPosMessage : public MessageBase
{
public:
    SetPosMessage();
    std::string processMessage(std::string incomingMsg);
};

#endif
