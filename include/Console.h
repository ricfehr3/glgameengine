#ifndef CONSOLE_H
#define CONSOLE_H

#include <SDL2/SDL.h>
#include <Shader.h>
#include <iostream>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

class Console
{
public:
    Console();
    void init();
    void draw();
    
private: 
    static bool m_show;
    Shader* mp_shader;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLuint m_bgtexture;
    GLuint m_lineTexture;
    
    std::vector<std::string> mv_oldLines;
    std::string currentLine;
    
    static SDL_mutex* m_mutex;
    
    void renderBackground();
    void renderLines();
    void renderCursor();
    
    void genBackgroundGL();
    void genCursorGL();
    
    void genBackgroundTexture();
    
    void getInput(const char* input);
    void processEntry();
    void removeLastChar();
    int updateLineTexture();
    bool rebuildLine;
    GLfloat w,h;
    
    void initFont();
    
    static const char DEFAULT_PROMPT[3];
    static const int  DEFAULT_PROMPT_LENGTH;
    static const int  DEFAULT_LINE_LENGTH;
    static const int  DEFAULT_LINE_CHARS;
    static const int  CONSOLE_CHARS_LEN;
    
    struct _ConsoleEntry
    {
        std::string entry;
        GLuint textureID;
    };
    
    std::vector<_ConsoleEntry> mv_consoleEntries;
    
    struct _ConsoleFont
    {
        FT_Library ft;
        FT_Face face;
        GLint font_size;
        GLint char_width;
        GLfloat advance;
        GLfloat line_height;
        GLfloat baseline;
    };
    
    _ConsoleFont consoleFont;
    GLint fontSize;
    
    std::string fontPath;
    
    static int triggerWatch(void *data, SDL_Event *e)
    {
        // hey, it fucking works! hot damn
        Console* console = static_cast<Console*>(data);
        
        if (SDL_LockMutex(m_mutex) != 0)
        {
            return 0;
        }
        // check for tilde
        if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_BACKQUOTE) 
        {
            if (m_show)
            {
                SDL_DelEventWatch(inputWatch, console);
                SDL_StopTextInput();
                m_show = false;
            } 
            else 
            {
                SDL_StartTextInput();
                SDL_AddEventWatch(inputWatch, console);
                m_show = true;
            }
        }

        SDL_UnlockMutex(m_mutex);
        return 0; /* return is ignored */
    }
    
    static int inputWatch (void *data, SDL_Event *e)
    {
        Console* console = static_cast<Console*>(data);
        
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
                console->removeLastChar();
                break;

            case SDLK_RETURN:
                //Console_NewLine(tty, tty->input_func, tty->input_func_data);
                console->processEntry();
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
            console->getInput(e->text.text);
            break;
        }

        SDL_UnlockMutex(m_mutex);
        return 0;
    }
};

#endif
