#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Model.h>
#include <Shader.h>
#include <Camera.h>
#include <GameWindow.h>
#include <GameComponent.h>
#include <RegisteredObject.h>

class GameObject : public RegisteredObject
{
public:
   GameObject(std::string name); 
   
   void setPosition(glm::vec3 newPos);
   void setEulerRotation(glm::vec3 newRot);
   void setScale(glm::vec3 newScale);
   glm::vec3 getPosition();
   glm::vec3 getEulerRotation();
   glm::vec3 getScale();
   void addComponent(GameComponent* component);
   
   void setCamera(Camera* camera);
   void setGameWindow(GameWindow* gameWindow);
   Camera* getCamera();
   GameWindow* getGameWindow();
   
   std::string getName();
   void setName(std::string);
   void onRenderUpdate();

protected:
    glm::vec3 m_position;
    glm::vec3 m_eulerRotation;
    glm::vec3 m_scale;
    
    Camera* mp_camera;
    GameWindow* mp_gameWindow;
    
    std::string m_name;
    
    virtual void userUpdate() = 0;
    
    
private:
    std::vector<GameComponent*> mv_gameComponenets;
};

#endif
