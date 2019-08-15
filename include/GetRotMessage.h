#ifndef GETROTMESSAGE_H
#define GETROTMESSAGE_H

#include <MessageBase.h>

class GetRotMessage : public MessageBase
{
public:
    GetRotMessage();
    std::string processMessage(std::string incomingMsg);
};

#endif
