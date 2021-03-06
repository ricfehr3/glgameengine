#include <GetPosMessage.h>
#include <MessagesManager.h>
#include <GameObjectList.h>

GetPosMessage::GetPosMessage()
{
    m_name = "getposmessage";
    m_messageFormat = "(get pos (.*?)) *$";
}

std::string GetPosMessage::processMessage(std::string incomingMsg)
{
    std::stringstream retss;
    std::istringstream iss(incomingMsg);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());
    if (checkExistGameObject(results[2]))
    {
        glm::vec3 pos = GameObjectList::getObjectByName(results[2])->getPosition();
        retss << "get pos " << results[2] << " " << pos.x << " " << pos.y << " " << pos.z;  
    }
    else
    {
        retss << "ERROR: GameObect: " << results[2] << " does not exist!";
    }

    GLOG_DEBUG(retss.str());
    return retss.str();
}

auto registerGetPosMessage = []
{
    MessagesManager::RegisterObject<GetPosMessage>();
    return 0;
}();
