#ifndef RENDEREDGAMEOBJECT_H
#define RENDEREDGAMEOBJECT_H

#include <GameObject.h>

class RenderedGameObject : public GameObject
{
public:
    RenderedGameObject(/*Model* model, Shader* shader, */std::string name);
    
    void userUpdate();
    
private:
    Model* mp_model;
    Shader* mp_shader;
};

#endif
