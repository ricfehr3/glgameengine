#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL2/SDL.h>

#include <string>
#include <stdexcept>

#include <Console.h>


class GameWindow
{
public:
    GameWindow(int width, int height, std::string programName);
    GameWindow() : GameWindow(800, 600, "test application") {}
   
    void init();
    void run();
    
    int width, height;
    
    SDL_Window *GetSDLWindow();
    void consoleHandler();
    
    Console m_console;
    
private:
    // SDL window, where all the magic happens
    SDL_Window *m_mainWindow;
    // GL context, so excited
    SDL_GLContext m_mainContext;
    //Console m_console;        
    std::string m_programName;
           
    void setOpenGLAttributes();
};

#endif
