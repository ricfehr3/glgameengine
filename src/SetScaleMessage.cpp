#include <SetScaleMessage.h>
#include <MessagesManager.h>
#include <GameObjectList.h>

SetScaleMessage::SetScaleMessage()
{
    m_name = "setscalemessage";
    m_messageFormat = "(set scale (.*?) [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+) [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+) [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)) *$";
}

std::string SetScaleMessage::processMessage(std::string incomingMsg)
{
    std::stringstream retss;
    std::istringstream iss(incomingMsg);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());
    if (checkExistGameObject(results[2]))
    {
        glm::vec3 newScale(
            ::atof(results[3].c_str()),
            ::atof(results[4].c_str()),
            ::atof(results[5].c_str()));

        GameObjectList::getObjectByName(results[2])->setScale(newScale);

        retss << "set scale " << results[2] << " " << newScale.x << " " << newScale.y << " " << newScale.z;  
    }
    else
    {
        retss << "ERROR: GameObect: " << results[2] << " does not exist!";
    }

    GLOG_DEBUG(retss.str());
    return retss.str();
}

auto registerSetScaleMessage = []
{
    MessagesManager::RegisterObject<SetScaleMessage>();
    return 0;
}();
