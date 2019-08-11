#include <GetPosMessage.h>
#include <MessagesManager.h>

GetPosMessage::GetPosMessage()
{
    m_name = "getposmessage";
    m_messageFormat = "GET <gameobject> POS";
}

std::string GetPosMessage::processMessage(std::string incomingMsg)
{
    std::stringstream ss(incomingMsg);
    std::string word;
    ss >> word;
    if (word != "get")
    {
        return "ERROR";
    }
    ss >> word;
    if (word != "cowboy")
    {
        return "ERROR";
    }
    ss >> word;
    if (word != "pos")
    {
        return "ERROR";
    }
    return "SUCCESS!";
}

auto registerGetPosMessage = []
{
    MessagesManager::RegisterObject<GetPosMessage>();
    return NULL;
}();
