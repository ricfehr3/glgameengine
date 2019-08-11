#ifndef GAMEOBJECTLIST_H
#define GAMEOBJECTLIST_H

#include <GameObject.h>
#include <ObjectRegistryManager.h>

#include <string>
#include <vector>

class GameObjectList : public ObjectRegistryManager<GameObject>
{
public:
    GameObjectList();
    
    void updateObjects();
    void add(GameObject* gameObject);
    void remove(std::string objectName);
    GameObject* getObject(std::string objectName);
    bool checkExistingName(std::string name);
    
    std::vector<std::string> getObjectNames();

private: 
    std::vector<GameObject*> m_gameObjectList;
};

#endif
