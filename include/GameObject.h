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

class GameObject
{
public:
   GameObject(Model* model, Shader* shader, std::string name); 
   
   void setPosition(glm::vec3 newPos);
   void setEulerRotation(glm::vec3 newRot);
   void setScale(glm::vec3 newScale);
   
   void setCamera(Camera* camera);
   void setGameWindow(GameWindow* gameWindow);
   
   std::string getName();
   void setName(std::string);

   void update();

private:
    glm::vec3 m_position;
    glm::vec3 m_eulerRotation;
    glm::vec3 m_scale;
    
    Model* mp_model;
    Shader* mp_shader;
    Camera* mp_camera;
    GameWindow* mp_gameWindow;
    
    std::string m_name;

    void setupObject();
};

#endif
