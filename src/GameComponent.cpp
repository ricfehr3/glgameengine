#include <GameComponent.h>
#include <GameObject.h>
#include <Logger.h>

void GameComponent::setGameObject(GameObject* gameObject)
{
    mp_gameObject = gameObject;
}

/*
std::string GameComponent::getName()
{
    if(m_name.empty())
    {
        GLOG_ERROR("Derived GameComponent has empty name");
        throw nameex;
    }
    return m_name;
}
*/
