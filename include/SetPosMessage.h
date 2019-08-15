#ifndef SETPOSMESSAGE_H
#define SETPOSMESSAGE_H

#include <MessageBase.h>

class SetPosMessage : public MessageBase
{
public:
    SetPosMessage();
    std::string processMessage(std::string incomingMsg);
private:
    bool checkExistGameObject(std::string name);
};

#endif
