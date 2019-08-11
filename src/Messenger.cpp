#include <chrono>
#include <future>
#include <algorithm>
#include <vector>
#include <sstream>

#include <Messenger.h>
#include <MessagesManager.h>

#include <glm/glm.hpp>

#include <GetPosMessage.h>

Messenger::Messenger()
{
    std::cout << "hmmmmmm" << std::endl;
    //GetPosMessage* message = new GetPosMessage();
    std::stringstream ss = MessagesManager::getRegisteredNames();
    std::string word;
    while (ss >> word)
    {
        std::cout << word << std::endl;
    }
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
    /*
    // convert to all lowercase
    std::transform(message.begin(), message.end(), message.begin(), ::tolower);
    std::string delimiter = " ";
    
    size_t pos = 0;
    std::string token;
    std::vector<std::string> messageWords;
    while ((pos = message.find(delimiter)) != std::string::npos) 
    {
        token = message.substr(0, pos);
        std::cout << token << std::endl;
        message.erase(0, pos + delimiter.length());
    }
    std::cout << message << std::endl;
    */
    
    // convert to all lowercase
    std::transform(message.begin(), message.end(), message.begin(), ::tolower);
    std::istringstream iss(message);
    std::string word;
    iss >> word;
    if(word == "get")
    {
        iss >> word;
        if(word == "gameobjectlist")
        {
            std::vector<std::string> nameList = mp_gameObjectList->getObjectNames();
            for (auto&& name: nameList)
            {   
                std::cout << name << std::endl;
            }
        }
        else
        {
            if(mp_gameObjectList->checkExistingName(word))
            {
                std::string objname = word;
                iss >> word;
                if(word == "pos")
                {
                    GameObject* obj = mp_gameObjectList->getObject(objname);
                    glm::vec3 pos = obj->getPosition();
                    std::cout << "x: " << pos.x << " y: " << pos.y << " z: " << pos.z << std::endl;
                }
                else if (word == "rot")
                {
                    GameObject* obj = mp_gameObjectList->getObject(objname);
                    glm::vec3 rot = obj->getEulerRotation();
                    std::cout << "x: " << rot.x << " y: " << rot.y << " z: " << rot.z << std::endl;
                }
                else if (word == "scale")
                {
                    GameObject* obj = mp_gameObjectList->getObject(objname);
                    glm::vec3 scale = obj->getScale();
                    std::cout << "x: " << scale.x << " y: " << scale.y << " z: " << scale.z << std::endl;
                }
                else
                {
                    std::cout << "ERROR! " << word << " is not a valid operator." << std::endl;
                }
            }
            else
            {
                std::cout << "ERROR! " << word << " is not a valid game object." << std::endl;
            }
        }
        //processGet(message);
    }
    else if (word == "set")
    {
        iss >> word;
        if(mp_gameObjectList->checkExistingName(word))
        {
            std::string objname = word;
            iss >> word;
            if(word == "pos")
            {
                float x,y,z;
                iss >> word;
                x = ::atof(word.c_str());
                iss >> word;
                y = ::atof(word.c_str());
                iss >> word;
                z = ::atof(word.c_str());
                
                GameObject* obj = mp_gameObjectList->getObject(objname);
                obj->setPosition(glm::vec3(x, y, z));
            }
            else if (word == "rot")
            {
                float x,y,z;
                iss >> word;
                x = ::atof(word.c_str());
                iss >> word;
                y = ::atof(word.c_str());
                iss >> word;
                z = ::atof(word.c_str());
                
                GameObject* obj = mp_gameObjectList->getObject(objname);
                obj->setEulerRotation(glm::vec3(x, y, z));
            }
            else if (word == "scale")
            {
                float x,y,z;
                iss >> word;
                x = ::atof(word.c_str());
                iss >> word;
                y = ::atof(word.c_str());
                iss >> word;
                z = ::atof(word.c_str());
                
                GameObject* obj = mp_gameObjectList->getObject(objname);
                obj->setScale(glm::vec3(x, y, z));
            }
            else
            {
                std::cout << "ERROR! " << word << " is not a valid operator." << std::endl;
            }
        }
        //processSet(message);
    }
    else
    {
        //std::cout << "ERROR! " << word << " is not a valid operator." << std::endl;
        return "ERROR! " + word + " is not a valid operator.";
    }
    return "cool beans";
}

void Messenger::processGet(std::string getString)
{
    int itr = 0;
    std::string tmpWord;
    // convert to all lowercase
    std::transform(getString.begin(), getString.end(), getString.begin(), ::tolower);
    std::istringstream iss(getString);
    while(iss >> tmpWord)
    {
        // remove "get"
        if(itr == 0)
        {
            iss >> tmpWord;
        }
        else if (tmpWord == "gameobjectlist")
        {
            std::vector<std::string> nameList = mp_gameObjectList->getObjectNames();
            for (auto&& name: nameList)
            {   
                std::cout << name << std::endl;
            }
        }
        //else if ()
        //{
        
        //}
        else
        {
            //if (tmp)
            
        }
    }
}

void Messenger::processSet(std::string setString)
{

}

std::atomic<bool> Messenger::m_running = ATOMIC_VAR_INIT(true);
