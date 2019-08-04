#ifndef GAMEOBJECTLIST_H
#define GAMEOBJECTLIST_H

#include <GameObject.h>

#include <string>
#include <vector>

class GameObjectList
{
public:
    GameObjectList();
    
    void updateObjects();
    void add(GameObject* gameObject);
    void remove(std::string objectName);

private: 
    std::vector<GameObject*> m_gameObjectList;
    bool checkExistingName(std::string name);
};

#endif
