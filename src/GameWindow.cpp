#include <GameWindow.h>

#include <glad/glad.h>

#include <iostream>

void CheckSDLError(int line = -1)
{
	std::string error = SDL_GetError();

	if (error != "")
	{
		error = "SLD Error : " + error;

		if (line != -1)
		{
			error = error + "\nLine : " + std::to_string(line) + "\n";
		}

		SDL_ClearError();
		
		throw std::runtime_error(error);
	}
}

GameWindow::GameWindow(int width, int height, std::string programName)
{
    this->width = width;
    this->height = height;
    m_programName = programName;
    m_console = Console();
}

SDL_Window *GameWindow::GetSDLWindow()
{
    return m_mainWindow;
}

void GameWindow::init()
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::runtime_error("Failed to init SDL video!");
	}
	
	// Create our window centered
	m_mainWindow = SDL_CreateWindow(m_programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		this->width, this->height, SDL_WINDOW_OPENGL);
		
	if (!m_mainWindow)
	{
	    CheckSDLError(__LINE__);
	}
	
	setOpenGLAttributes();
	
	// Create our opengl context and attach it to our window
	m_mainContext = SDL_GL_CreateContext(m_mainWindow);
	if (m_mainContext == NULL)
	{
	    CheckSDLError(__LINE__);
	}
	
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
	
	// Make this a configurable option. It is vsync on/off
	SDL_GL_SetSwapInterval(0);
	
	// Lock mouse to screen 
	//SDL_SetWindowGrab(m_mainWindow, SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	//SDL_CaptureMouse(SDL_TRUE); // this just allows sdl to get all mouse events even outside of the window, whoops
	
	std::cout << "Running with opengl version: " <<  glGetString(GL_VERSION) << std::endl;
}

void GameWindow::setOpenGLAttributes()
{
	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.3 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}
