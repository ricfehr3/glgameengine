#include <chrono>
#include <future>
#include <algorithm>
#include <vector>
#include <sstream>

#include <Messenger.h>
#include <MessagesManager.h>
#include <MessageBase.h>

#include <glm/glm.hpp>

Messenger::Messenger()
{
    //GetPosMessage* message = new GetPosMessage();
    /*
    std::stringstream ss = MessagesManager::getRegisteredNames();
    std::string word;
    while (ss >> word)
    {
        std::cout << word << std::endl;
    }
    */
}

void Messenger::run()
{
    /*
    std::string line;
    while(m_running)
    {  
        while(std::getline(std::cin, line) && m_running) //read entire lines at a time
        {
	       std::cout << line << std::endl;  
        }
    }
    */
}

void Messenger::stop()
{
    m_running = false;
}

void Messenger::setGameObjectList(GameObjectList* app)
{
    mp_gameObjectList = app;
}

// be really cool if I could use like reflection or a callback function to make a config file for this
std::string Messenger::processString(std::string message)
{ 
    std::transform(message.begin(), message.end(), message.begin(), ::tolower);
    bool foundMsg = false;
    std::stringstream ss(message);
    std::stringstream retss;
    std::string tmp;
    int argCount = 0;
    while(ss >> tmp)
    {
        argCount++;
    }
    
    // enumerate all messages in map
    std::map<std::string, MessageBase*>mapTest = MessagesManager::GetObjectMap();
    for (auto& it : mapTest) 
    {
        // compare argument length to message argument length
        if(it.second->matchFormat(message))
        {
            retss << it.second->processMessage(message);
            GLOG_DEBUG(retss.str());
            foundMsg = true;
            //break;
        }
    }

    if(!foundMsg)
    {
        retss << "Error could not find message match for: " << message;
        GLOG_DEBUG(retss.str());
    }

    return retss.str();
}

void Messenger::processSet(std::string setString)
{

}

std::atomic<bool> Messenger::m_running = ATOMIC_VAR_INIT(true);
