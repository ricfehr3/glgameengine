#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

/*
 * Abstract class for all components to be added to game obejcts. The idea is 
 * the game object abstract class is going to have a vector of these. Each of
 * these will have there own onRenderUpdate function which each game object will
 * be responsible for updateing. But it's going to be in the private scope of 
 * the game object class so you can freely add and remove components.
 * this should make it so you can easily make custom objects in real time (i.e.
 * for editing). But I guess you can exploit it for a more customizeable game.
 * like a game where you can chose certain types of game componenets to add to
 * game objects. For example, car updgrades. Weapon upgrades. That kinda shit.
 * Should be pretty cool once it's all done. Also I just wanted to take a minute
 * to say that that new tool album is pretty fucking good. Well at least the one
 * song they released today (fucking finally).
 */

// include this to make writing these easier
#include <glm/glm.hpp>

#include <vector>
#include <string>
 
#include <RegisteredObject.h>
 
// forward declare to avoid a circular dependency
class GameObject;

class GameComponent : public RegisteredObject
{
public:
    virtual void onRenderUpdate() = 0;
    //std::string getName();
    void setGameObject(GameObject* gameObject);
    void printNothing();
        
protected:
    GameObject* mp_gameObject;
    //std::string m_name;
    //nonameexception nameex;
};

#endif

