#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <GameObjectList.h>

#include <string>

class GameScene
{
public:
    GameScene(std::string sceneName);
    std::string getName(std::string);
    void setActive();
    void disable();
private:
    std::string m_name;
    GameObjectList m_objectList;
};

#endif
