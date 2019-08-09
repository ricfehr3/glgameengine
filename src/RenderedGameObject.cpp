#include <RenderedGameObject.h>

RenderedGameObject::RenderedGameObject(/*Model* model, Shader* shader, */std::string name) : GameObject(name)
{
    //mp_model = model;
    //mp_shader = shader;
}

void RenderedGameObject::userUpdate()
{
    /*
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
        model = glm::translate(model, m_position); 
        model = glm::rotate(model, glm::radians(m_eulerRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_eulerRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_eulerRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, m_scale);
        mp_shader->setMat4("model", model);
        
        mp_model->Draw(*mp_shader);
        
    }
    */
}
