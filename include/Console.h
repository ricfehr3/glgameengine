#ifndef CONSOLE_H
#define CONSOLE_H

#include <SDL2/SDL.h>
#include <Shader.h>
#include <iostream>

class Console
{
public:
    Console();
    void draw();
    
private: 
    static bool m_show;
    Shader* m_shader;
    static SDL_mutex* m_mutex;
    
    void renderBackground();
    
    static int triggerWatch(void *data, SDL_Event *e)
    {
        if (SDL_LockMutex(m_mutex) != 0)
        {
            return 0;
        }
        std::cout << "turds" << m_show << std::endl;
        // check for tilde
        if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_BACKQUOTE) 
        {
            std::cout << m_show << std::endl;
            if (m_show)
            {
                std::cout << m_show << std::endl;
                SDL_DelEventWatch(inputWatch, NULL);
                SDL_StopTextInput();
                m_show = false;
            } 
            else 
            {
                std::cout << m_show << std::endl;
                SDL_StartTextInput();
                SDL_AddEventWatch(inputWatch, NULL);
                m_show = true;
            }
        }

        SDL_UnlockMutex(m_mutex);
        return 0; /* return is ignored */
    }
    
    static int inputWatch (void *data, SDL_Event *e)
    {
        if (SDL_LockMutex(m_mutex) != 0) 
        {
            return 0;
        }

        if (!m_show)
        {
            SDL_UnlockMutex(m_mutex);
            return 0;
        }

        switch (e->type) 
        {
        case SDL_KEYDOWN:
            switch (e->key.keysym.sym) 
            {
            case SDLK_BACKSPACE:
                //_Console_remove_input(tty);
                break;

            case SDLK_RETURN:
                //Console_NewLine(tty, tty->input_func, tty->input_func_data);
                break;

            /* copy */
            case SDLK_c:
                //if (SDL_GetModState() & KMOD_CTRL) {
                    /* SDL_SetClipboardText(tty->curr_line->input) */
                //}
                break;

            /* paste */
            case SDLK_v:
                //if (SDL_GetModState() & KMOD_CTRL) {
                    /* Console_GetInput(tty, SDL_GetClipboardText()); */
                //}
                break;

            case SDLK_UP:
                //Console_SetCurrLine(tty, LINE_UP);
                break;

            case SDLK_DOWN:
                //Console_SetCurrLine(tty, LINE_DOWN);
                break;

            case SDLK_LEFT:
                //if (tty->cursor > 0) {
                //    tty->cursor--;
                //    tty->rebuild_line = true;
                //}
                break;

            case SDLK_RIGHT:
                //if (tty->cursor < tty->max_input && 
                //        tty->cursor < tty->curr_line->len) {
                //    tty->cursor++;
                //    tty->rebuild_line = true;
                //}
                break;
            }
            break;

        case SDL_TEXTINPUT:
            //_Console_get_input(tty, e->text.text);
            break;
        }

        SDL_UnlockMutex(m_mutex);
        return 0;
    }
};

#endif
