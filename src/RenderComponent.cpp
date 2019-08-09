#include <RenderComponent.h>

RenderComponent::RenderComponent(char* modelPath, const GLchar* vertexPath, const GLchar* fragmentPath)
{
    mp_model = new Model(modelPath);
    mp_shader = new Shader(vertexPath, fragmentPath);
}

void RenderComponent::onRenderUpdate()
{
    mp_shader->use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(
            glm::radians(mp_gameObject->getCamera()->Zoom), 
            (float)mp_gameObject->getGameWindow()->width / 
            (float)mp_gameObject->getGameWindow()->height, 0.1f, 100.0f);
    glm::mat4 view = mp_gameObject->getCamera()->GetViewMatrix();
    mp_shader->setMat4("projection", projection);
    mp_shader->setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, mp_gameObject->getPosition()); 
    model = glm::rotate(
            model, 
            glm::radians(mp_gameObject->getEulerRotation().x), 
            glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(
            model, 
            glm::radians(mp_gameObject->getEulerRotation().y),
            glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(
            model, 
            glm::radians(mp_gameObject->getEulerRotation().z), 
            glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, mp_gameObject->getScale());
    mp_shader->setMat4("model", model);
    
    mp_model->Draw(*mp_shader);
}
