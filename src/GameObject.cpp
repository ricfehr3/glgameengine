#include "GameObject.h"

GameObject::GameObject(std::string name)
{
    m_name = name;
}

void GameObject::setPosition(glm::vec3 newPos)
{
    m_position = newPos;
}

void GameObject::setEulerRotation(glm::vec3 newRot)
{
    m_eulerRotation = newRot;
}

void GameObject::setScale(glm::vec3 newScale)
{
    m_scale = newScale;
}

glm::vec3 GameObject::getPosition()
{
    return m_position;
}

glm::vec3 GameObject::getEulerRotation()
{
    return m_eulerRotation;
}

glm::vec3 GameObject::getScale()
{
    return m_scale;
}

void GameObject::setCamera(Camera* camera)
{
    mp_camera = camera;
}


void GameObject::setGameWindow(GameWindow* gameWindow)
{
    mp_gameWindow = gameWindow;
}

Camera* GameObject::getCamera()
{
    return mp_camera;
}

GameWindow* GameObject::getGameWindow()
{
    return mp_gameWindow;
}

std::string GameObject::getName()
{
    return m_name;
}

void GameObject::setName(std::string name)
{
    m_name = name;
}

void GameObject::addComponent(GameComponent* component)
{
    component->setGameObject(this);
    mv_gameComponenets.push_back(component);
}


void GameObject::onRenderUpdate()
{
    for (const auto &component : mv_gameComponenets) 
    {
        component->onRenderUpdate();
    }
    userUpdate();
}
