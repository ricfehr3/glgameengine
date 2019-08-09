#ifndef GAMECOMPONENTMANAGER_H
#define GAMECOMPONENTMANAGER_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <GameComponent.h>

class  GameComponentManager
{
public:
    GameComponentManager();
    ~GameComponentManager();
    
    //std::vector<std::string> getRegisteredNames()
    static /*std::vector<std::string>*/ void getRegisteredNames()
    {
        // Game component registry testing
        GameComponentRegistry& registry(GameComponentRegistry::get());
        for(GameComponentRegistry::iterator it = registry.begin(); it != registry.end(); ++it)
        {
            GameComponent_creator func = *it;
            GameComponent* _ptr = func();
            std::shared_ptr<GameComponent> ptr(_ptr);
            //ptr->printNothing();
            std::cout << "I hope this fucking works: " << ptr->getName() << std::endl;
            //RenderComponent* fart = static_cast<RenderComponent*>(_ptr);
            //fart->testfart();
        }
    }
    
private:
};

#endif
