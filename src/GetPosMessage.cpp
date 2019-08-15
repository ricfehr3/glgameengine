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
        retss << "get " << results[2] << " pos " << pos.x << " " << pos.y << " " << pos.z;  
    }
    else
    {
        retss << "ERROR: GameObect: " << results[2] << " does not exist!";
    }

    GLOG_DEBUG(retss.str());
    return retss.str();
}

bool GetPosMessage::checkExistGameObject(std::string name)
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

auto registerGetPosMessage = []
{
    MessagesManager::RegisterObject<GetPosMessage>();
    return 0;
}();
