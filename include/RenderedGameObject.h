#ifndef RENDEREDGAMEOBJECT_H
#define RENDEREDGAMEOBJECT_H

#include <GameObject.h>

class RenderedGameObject : public GameObject
{
public:
    RenderedGameObject(std::string name);
    
    void userUpdate();
    
private:
    Model* mp_model;
    Shader* mp_shader;
};

#endif
