#include <MessageBase.h>
#include <GameObjectList.h>
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

bool MessageBase::checkExistGameObject(std::string name)
{
    bool ret = false;
    std::string compname;
    std::stringstream ss = GameObjectList::getRegisteredNames();
    while(ss >> compname)
    {
        if(compname == name)
        {
            ret = true;
        }
    }
    return ret;
}