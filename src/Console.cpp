#include <Console.h>

Console::Console()
{
    m_show = false;
    m_shader = new Shader();
    
    //    m_shader->compile("shaders/Console/console.vs", "shaders/Console/console.fs");

    SDL_AddEventWatch(triggerWatch, NULL);
}

void Console::draw()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if(m_show)
    {
        //m_shader.use();
    }
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
}

bool Console::m_show = false;
SDL_mutex* Console::m_mutex = SDL_CreateMutex();
