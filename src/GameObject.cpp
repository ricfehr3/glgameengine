#include "GameObject.h"

/*
GameObject::GameObject(Model* model, Shader* shader, std::string name)
{
    mp_model = model;
    mp_shader = shader;
    
    m_name = name;
}
*/

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

/*
void GameObject::update()
{
    // todo, add logging and better debug besides cout
    bool canRender = false;
    if (mp_camera == nullptr)
        std::cout << "ERROR! Can't render object, no Camera reference!" << std::endl;
    else if (mp_gameWindow == nullptr)
        std::cout << "ERROR! Can't render object, no GameWindow reference!" << std::endl;
    else if (mp_shader == nullptr)
        std::cout << "ERROR! Can't render object, no Shader reference!" << std::endl;
    else if (mp_model == nullptr)
        std::cout << "ERROR! Can't render object, no model reference!" << std::endl;
    else
        canRender = true;
        
    if(canRender)
    {
        mp_shader->use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(mp_camera->Zoom), (float)mp_gameWindow->width / (float)mp_gameWindow->height, 0.1f, 100.0f);
        glm::mat4 view = mp_camera->GetViewMatrix();
        mp_shader->setMat4("projection", projection);
        mp_shader->setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_position); // translate it down so it's at the center of the scene
        model = glm::rotate(model, glm::radians(m_eulerRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_eulerRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_eulerRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, m_scale);	// it's a bit too big for our scene, so scale it down
        mp_shader->setMat4("model", model);
        
        mp_model->Draw(*mp_shader);
    }
}
*/
