#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <Camera.h>
#include <GameWindow.h>
#include <GameObject.h>
#include <GameObjectList.h>

class GameApplication
{
public:
    GameApplication(Camera* camera);
    
    void init();
    void run();
    
    void addGameObject(GameObject* gameObjectToAdd);
    
    GameObjectList gameObjects;
    
    float deltaTime;

private:
    bool m_gameloop;
    bool m_menuMode;
    Camera* mp_camera;
    GameWindow* mp_gameWindow;
};

#endif
