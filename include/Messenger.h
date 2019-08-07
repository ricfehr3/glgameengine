#ifndef MESSENGER_H
#define MESSENGER_H

#include <iostream>
#include <string>
#include <atomic>

#include <GameObjectList.h>
#include <GameObject.h>

class Messenger
{
public:
    Messenger();
    void run();
    void stop();
    
    void setGameObjectList(GameObjectList* objectList);
    void processString(std::string message);
    
private:
    static std::atomic<bool> m_running;
    GameObjectList* mp_gameObjectList;
};

#endif
