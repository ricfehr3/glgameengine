#include <GetScaleMessage.h>
#include <MessagesManager.h>
#include <GameObjectList.h>

GetScaleMessage::GetScaleMessage()
{
    m_name = "getscalemessage";
    m_messageFormat = "(get scale (.*?)) *$";
}

std::string GetScaleMessage::processMessage(std::string incomingMsg)
{
    std::stringstream retss;
    std::istringstream iss(incomingMsg);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());
    if (checkExistGameObject(results[2]))
    {
        glm::vec3 scale = GameObjectList::getObjectByName(results[2])->getScale();
        retss << "get scale " << results[2] << " " << scale.x << " " << scale.y << " " << scale.z;  
    }
    else
    {
        retss << "ERROR: GameObect: " << results[2] << " does not exist!";
    }

    GLOG_DEBUG(retss.str());
    return retss.str();
}

auto registerGetScaleMessage = []
{
    MessagesManager::RegisterObject<GetScaleMessage>();
    return 0;
}();
