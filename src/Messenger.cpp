#include <chrono>
#include <future>

#include <Messenger.h>

#include <glm/glm.hpp>

Messenger::Messenger()
{
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

void Messenger::processString(std::string message)
{
    std::cout << "messenger got: " << message << std::endl;
    if(message == "poopy")
    {
        std::vector<std::string> nameList = mp_gameObjectList->getObjectNames();
        for (auto&& name: nameList)
        {   
            std::cout << name << std::endl;
        }
    }
    if(message == "shit")
    {
        GameObject* obj = mp_gameObjectList->getObject("turd man");
        
        if(obj != nullptr)
        {
            obj->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        }
        else
        {
            std::cout << "could not find turd man, dude" << std::endl;
        }
        
    }
}

std::atomic<bool> Messenger::m_running = ATOMIC_VAR_INIT(true);
