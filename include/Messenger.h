#ifndef MESSENGER_H
#define MESSENGER_H

#include <iostream>
#include <string>
#include <atomic>
#include <sstream>

#include <GameObjectList.h>
#include <GameObject.h>

class Messenger
{
public:
    Messenger();
    void run();
    void stop();
    
    void setGameObjectList(GameObjectList* objectList);
    std::string processString(std::string message);
    void processGet(std::string getString);
    void processSet(std::string setString);
    
private:
    static std::atomic<bool> m_running;
    GameObjectList* mp_gameObjectList;
};

#endif
