#include <GameObjectList.h>

#include <iostream>

GameObjectList::GameObjectList()
{

}

void GameObjectList::updateObjects()
{
    for (const auto &gameObject : m_gameObjectList) 
    {
        gameObject->update();
    }
}

void GameObjectList::add(GameObject* gameObject)
{
    //if(checkExistingName(gameObject->getName()))
    //{
    //    gameObject->setName(gameObject->getName()+"_1");
    //}
    m_gameObjectList.push_back(gameObject);
}

void GameObjectList::remove(std::string objectName)
{
    std::vector<GameObject*>::iterator it;
    for( it = std::begin(m_gameObjectList); it != std::end(m_gameObjectList);)
    {
        if (objectName == (*it)->getName())
        {
            m_gameObjectList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

bool GameObjectList::checkExistingName(std::string objectName)
{
    bool returnVal = false;
    std::vector<GameObject*>::iterator it;
    for( it = std::begin(m_gameObjectList); it != std::end(m_gameObjectList);)
    {
        if (objectName == (*it)->getName())
        {
            returnVal = true;
        }
    }
    return returnVal;
}
