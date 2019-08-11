#include <GetPosMessage.h>
#include <MessagesManager.h>

GetPosMessage::GetPosMessage()
{
    m_name = "getposmessage";
}

auto registerGetPosMessage = []
{
    MessagesManager::RegisterObject<GetPosMessage>();
    return NULL;
}();
