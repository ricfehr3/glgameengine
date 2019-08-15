#include <SetRotMessage.h>
#include <MessagesManager.h>
#include <GameObjectList.h>

SetRotMessage::SetRotMessage()
{
    m_name = "setrotmessage";
    m_messageFormat = "(set rot (.*?) [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+) [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+) [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)) *$";
}

std::string SetRotMessage::processMessage(std::string incomingMsg)
{
    std::stringstream retss;
    std::istringstream iss(incomingMsg);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());
    if (checkExistGameObject(results[2]))
    {
        glm::vec3 newRot(
            ::atof(results[3].c_str()),
            ::atof(results[4].c_str()),
            ::atof(results[5].c_str()));

        GameObjectList::getObjectByName(results[2])->setEulerRotation(newRot);

        retss << "set rot " << results[2] << " " << newRot.x << " " << newRot.y << " " << newRot.z;  
    }
    else
    {
        retss << "ERROR: GameObect: " << results[2] << " does not exist!";
    }

    GLOG_DEBUG(retss.str());
    return retss.str();
}

auto registerSetRotMessage = []
{
    MessagesManager::RegisterObject<SetRotMessage>();
    return 0;
}();
