#ifndef GETPOSMESSAGE_H
#define GETPOSMESSAGE_H

#include <MessageBase.h>

class GetPosMessage : public MessageBase
{
public:
    GetPosMessage();
    std::string processMessage(std::string incomingMsg);
private:
    bool checkExistGameObject(std::string name);
};

#endif
