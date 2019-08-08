#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <GameComponent.h>
#include <GameObject.h>
#include <Model.h>
#include <Shader.h>

/*
 * Render component 
 */

class RenderComponent : public GameComponent
{
public:
    RenderComponent(char* modelPath, const GLchar* vertexPath, const GLchar* fragmentPath);
    void onRenderUpdate();
private:
    Model* mp_model;
    Shader* mp_shader;
};

#endif
