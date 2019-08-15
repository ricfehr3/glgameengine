#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <mutex>

#include <Camera.h>
#include <GameWindow.h>
#include <GameObject.h>
#include <GameObjectList.h>
#include <Messenger.h>
#include <Logger.h>

class GameApplication
{
public:
    GameApplication(Camera* camera);
    
    void init();
    void run();
    
    void addGameObject(GameObject* gameObjectToAdd);
    
    GameObjectList gameObjects;
    
    //float deltaTime;

private:
    bool m_gameloop;
    bool m_menuMode;
    Camera* mp_camera;
    GameWindow* mp_gameWindow;
    Messenger m_messenger;
    std::mutex m_gameMutex;
    
    GameLogger::Logger* m_logger;
    
    void runGameLoop();
};

#endif
