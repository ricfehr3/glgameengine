#ifndef GETSCALEMESSAGE_H
#define GETSCALEMESSAGE_H

#include <MessageBase.h>

class GetScaleMessage : public MessageBase
{
public:
    GetScaleMessage();
    std::string processMessage(std::string incomingMsg);
};

#endif
