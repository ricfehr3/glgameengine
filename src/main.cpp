#include <glm/glm.hpp>

#include <GameApplication.h>
#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <RenderedGameObject.h>
#include <RenderComponent.h>
#include <testComp.h>

#include <iostream>

// todo find a way to update each game object
// add numbers to existing names in game object list
// implement the idea of a scene into the engine

int main()
{
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    GameApplication app(&camera);
    try 
    {
        app.init();

        Shader ourShader("shaders/1.model_loading.vs", "shaders/1.model_loading.fs");
        Model ourModel("models/cowboi/man_textured.obj");
        
        RenderedGameObject cowboy(&ourModel, &ourShader, "cowboy");
        cowboy.setPosition(glm::vec3(0.0f, -1.75f, 0.0f));
        cowboy.setScale(glm::vec3(0.2f, 0.2f, 0.2f));
        cowboy.setEulerRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        
        testComp* test = new testComp;
        RenderComponent* rendComp = new RenderComponent("models/cowboi/man_textured.obj", "shaders/1.model_loading.vs", "shaders/1.model_loading.fs");
        
        cowboy.addComponent(test);
        cowboy.addComponent(rendComp);
        
        app.addGameObject(&cowboy);
         
        app.run();
    }
    catch (const std::exception &e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
   
    return 0;
}
