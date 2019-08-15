#include <MessageBase.h>
#include <Logger.h>
#include <sstream>

MessageBase::MessageBase()
{
}

bool MessageBase::matchFormat(std::string incomingMsg)
{
    bool ret = false;
    if(regex_match(incomingMsg, m_messageFormat))
    {
        ret = true;
    }
    return ret;
}