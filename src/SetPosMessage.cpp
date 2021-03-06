#include <SetPosMessage.h>
#include <MessagesManager.h>
#include <GameObjectList.h>

SetPosMessage::SetPosMessage()
{
    m_name = "setposmessage";
    m_messageFormat = "(set pos (.*?) [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+) [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+) [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)) *$";
}

std::string SetPosMessage::processMessage(std::string incomingMsg)
{
    std::stringstream retss;
    std::istringstream iss(incomingMsg);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());
    if (checkExistGameObject(results[2]))
    {
        glm::vec3 newPos(
            ::atof(results[3].c_str()),
            ::atof(results[4].c_str()),
            ::atof(results[5].c_str()));

        GameObjectList::getObjectByName(results[2])->setPosition(newPos);

        retss << "set pos " << results[2] << " " << newPos.x << " " << newPos.y << " " << newPos.z;  
    }
    else
    {
        retss << "ERROR: GameObect: " << results[2] << " does not exist!";
    }

    GLOG_DEBUG(retss.str());
    return retss.str();
}

auto registerSetPosMessage = []
{
    MessagesManager::RegisterObject<SetPosMessage>();
    return 0;
}();
