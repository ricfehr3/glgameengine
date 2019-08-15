#ifndef SETROTMESSAGE_H
#define SETROTMESSAGE_H

#include <MessageBase.h>

class SetRotMessage : public MessageBase
{
public:
    SetRotMessage();
    std::string processMessage(std::string incomingMsg);
};

#endif
