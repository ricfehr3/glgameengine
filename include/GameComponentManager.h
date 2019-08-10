#ifndef GAMECOMPONENTMANAGER_H
#define GAMECOMPONENTMANAGER_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <GameComponent.h>
#include <ObjectRegistryManager.h>
#include <RenderComponent.h>

class  GameComponentManager
{
public:
    GameComponentManager();
    ~GameComponentManager();
    
    //std::vector<std::string> getRegisteredNames()
    static /*std::vector<std::string>*/ void getRegisteredNames()
    {
        ObjectRegistryManager<GameComponent>::ObjectRegistry& registry(ObjectRegistryManager<GameComponent>::ObjectRegistry::get());
        for(ObjectRegistryManager<GameComponent>::ObjectRegistry::iterator it = registry.begin(); it != registry.end(); ++it)
        {
            GameComponent* func = *it;
            std::cout << "Component names: " << func->getName() << std::endl;
        }
    }
    
private:
};

#endif
