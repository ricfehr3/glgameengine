#include <GetRotMessage.h>
#include <MessagesManager.h>
#include <GameObjectList.h>

GetRotMessage::GetRotMessage()
{
    m_name = "getrotmessage";
    m_messageFormat = "(get rot (.*?)) *$";
}

std::string GetRotMessage::processMessage(std::string incomingMsg)
{
    std::stringstream retss;
    std::istringstream iss(incomingMsg);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());
    if (checkExistGameObject(results[2]))
    {
        glm::vec3 rot = GameObjectList::getObjectByName(results[2])->getEulerRotation();
        retss << "get rot " << results[2] << " " << rot.x << " " << rot.y << " " << rot.z;  
    }
    else
    {
        retss << "ERROR: GameObect: " << results[2] << " does not exist!";
    }

    GLOG_DEBUG(retss.str());
    return retss.str();
}

auto registerGetRotMessage = []
{
    MessagesManager::RegisterObject<GetRotMessage>();
    return 0;
}();
