#ifndef GAMECOMPONENTMANAGER_H
#define GAMECOMPONENTMANAGER_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>

#include <GameComponent.h>
#include <ObjectRegistryManager.h>
#include <RenderComponent.h>
#include <ObjectRegistryManager.h>

// Chosing inheritance over composition on these. They won't go into a list or 
// anything. It just makes more sense to do it this way. The code looks way better
// and would seem to be more readable
class  GameComponentManager : public ObjectRegistryManager<GameComponent>
{
public:
    GameComponentManager();
    ~GameComponentManager();

    /*    
    static std::stringstream getRegisteredNames()
    {
        std::stringstream registeredNames;
        // lamda to get rid of static errors with calling the getName function
        auto getName = [] (GameComponent* gameComponent) {return gameComponent->getName();};
        ObjectRegistry& registry(ObjectRegistry::get());
        for(ObjectRegistry::iterator it = registry.begin(); it != registry.end(); ++it)
        {
            GameComponent* comp = *it;
            registeredNames << getName(comp) << " ";
        }
        return registeredNames;
    }
    */
    
private:
};

#endif
