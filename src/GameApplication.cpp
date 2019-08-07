#include <GameApplication.h>

#include <thread>
#include <chrono>

GameApplication::GameApplication(Camera* camera)
{
    mp_gameWindow = new GameWindow();
    gameObjects = GameObjectList();
    m_messenger = Messenger();
    m_messenger.setGameObjectList(&gameObjects);
    
    mp_camera = camera;
    
    deltaTime = 0.0f;
    
    m_gameloop = false;
    m_menuMode = false;
}

void GameApplication::init()
{
    mp_gameWindow->init();
}

void GameApplication::run()
{       
    //std::thread messagerLoopThread(&Messenger::run, std::ref(m_messenger));
    //std::thread messagerLoopThread(&Messenger::run, m_messenger);
    
    runGameLoop();
    //messagerLoopThread.join();
}

void GameApplication::addGameObject(GameObject* gameObjectToAdd)
{
    gameObjectToAdd->setCamera(mp_camera);
    gameObjectToAdd->setGameWindow(mp_gameWindow);
    gameObjects.add(gameObjectToAdd);
}

void GameApplication::runGameLoop()
{
    Shader ourShader("shaders/1.model_loading.vs", "shaders/1.model_loading.fs");
    Model ourModel("models/nanosuit/nanosuit.obj");

    GameObject nanoman2(&ourModel, &ourShader, "pee pee man");
    nanoman2.setPosition(glm::vec3(0.0f, 1.75f, 0.0f));
    nanoman2.setScale(glm::vec3(0.2f, 0.2f, 0.2f));
    nanoman2.setEulerRotation(glm::vec3(0.0f, 0.0f, 0.0f));

   
    // thinking about making this an enum to pause the game... somehow
	m_gameloop = true;
    
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
   
    uint64_t lastFrame = SDL_GetPerformanceCounter();

	while (m_gameloop)
	{
	    uint64_t currentFrame = SDL_GetPerformanceCounter();
        uint64_t framesElapsed = currentFrame - lastFrame;
        deltaTime = (float)(framesElapsed / (1000000000.0f));
        lastFrame = currentFrame;
	
	    // add an input class here
	    const unsigned char* keystates = SDL_GetKeyboardState(NULL);
	    
	    if(keystates[SDL_SCANCODE_W])
	    {
	        mp_camera->ProcessKeyboard(FORWARD, deltaTime);
	    }
	    if(keystates[SDL_SCANCODE_S])
	    {
	        mp_camera->ProcessKeyboard(BACKWARD, deltaTime);
	    }
	    if(keystates[SDL_SCANCODE_A])
	    {
	        mp_camera->ProcessKeyboard(LEFT, deltaTime);
	    }
	    if(keystates[SDL_SCANCODE_D])
	    {
	        mp_camera->ProcessKeyboard(RIGHT, deltaTime);
	    }
		
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				m_gameloop = false;
				m_messenger.stop();
			}

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				    case SDLK_ESCAPE:
				        if(m_menuMode)
				        {
				            SDL_SetRelativeMouseMode(SDL_TRUE);
				            m_menuMode = false;
				        }
				        else
				        {   
				            SDL_SetRelativeMouseMode(SDL_FALSE);
				            m_menuMode = true;
				        }
					    break;
                    //case SDL_VIDEORESIZE:
                        //break;
				    case SDLK_m:
                        addGameObject(&nanoman2);
				        break;
				    case SDLK_n:
                        gameObjects.remove("pee pee man");
				        break;
				    default:
					    break;
				}
			}
			
			if(event.type == SDL_MOUSEMOTION)
			{
			    if (!m_menuMode)
			    {
                    int MovementX, MovementY;
                    SDL_GetRelativeMouseState(&MovementX, &MovementY);

                    mp_camera->ProcessMouseMovement(MovementX, -MovementY);
                }
            }          
		}

		// Clear the screen
		glClearColor(0.05f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // ALL THE GAME LOGIC HERE
        gameObjects.updateObjects();
        mp_gameWindow->m_console.draw();

        SDL_GL_SwapWindow(mp_gameWindow->GetSDLWindow());
        
        if(mp_gameWindow->m_console.inputReady())
        {
            m_messenger.processString(mp_gameWindow->m_console.getInput());
        }
    }
}

void GameApplication::turds()
{
    std::cout << "turds" << std::endl;
}
