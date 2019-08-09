#include <GameComponent.h>
#include <GameObject.h>
#include <Logger.h>

void GameComponent::setGameObject(GameObject* gameObject)
{
    mp_gameObject = gameObject;
}

std::string GameComponent::getName()
{
    if(m_name.empty())
    {
        GLOG_ERROR("Derived GameComponent has empty name");
        throw nameex;
    }
    return m_name;
}

GameComponentRegistry& GameComponentRegistry::get()
{
    static GameComponentRegistry instance;
    return instance;
}

void GameComponentRegistry::add(GameComponent_creator creator)
{
    mv_GameComponents.push_back(creator);
}

GameComponentRegistry::iterator GameComponentRegistry::begin()
{
    return mv_GameComponents.begin();
}

GameComponentRegistry::iterator GameComponentRegistry::end()
{ return mv_GameComponents.end(); }

GameComponentRegistration::GameComponentRegistration(GameComponent_creator creator)
{
    GameComponentRegistry::get().add(creator);
}
