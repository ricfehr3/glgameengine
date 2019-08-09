#ifndef CONSOLE_H
#define CONSOLE_H

#include <SDL2/SDL.h>
#include <Shader.h>
#include <iostream>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

// Todo, add throw if no window. Default constructor needed

class Console
{
public:
    Console();
    ~Console();
    void init();
    void draw();
    void setWindow(SDL_Window* window);
    bool inputReady();
    void setOutput(std::string output);
    std::string getInput();
    
private: 
    // enums
    enum ENTRY_DIR
    {
        LINE_UP, LINE_DOWN
    };
    
    // structs
    struct _ConsoleEntry
    {
        std::string entry;
        GLuint textureID;
        GLfloat w;
        GLfloat h;
    };
    
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
    
    // OpenGL Stuff
    Shader* mp_shader;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_bgtexture;
    GLuint m_cursortexture;
    void renderBackground();
    void renderLines();
    void renderCursor();
    void initGL();
    void genConsoleTexture(GLuint &texID);
    
    //SDL Stuff
    SDL_Window* mp_window;
    static SDL_mutex* m_mutex;
    
    std::vector<std::string> mv_oldLines;
    //std::string currentLine;


    _ConsoleFont consoleFont;
    GLint fontSize;
    std::string fontPath;
    float wrap_len;
    unsigned int currLineNum;
    bool rebuildLine;
    // cursors position on console
    unsigned int cursor;
    int m_winWidth, m_winHeight;
    void getWindowDimensions();
    bool m_inputReady;
    static bool m_show;
    std::vector<_ConsoleEntry> mv_consoleEntries;
    
    void initFont();
    void getInput(const char* input);
    void processEntry();
    void removeLastChar();
    int updateLineTexture();
    void SetCurrLine(ENTRY_DIR dir);
    GLfloat w,h;
    
   
    static const char DEFAULT_PROMPT[3];
    static const int  DEFAULT_PROMPT_LENGTH;
    static const int  DEFAULT_LINE_LENGTH;
    static const int  DEFAULT_LINE_CHARS;
    static const int  CONSOLE_CHARS_LEN;
    
    
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
                console->processEntry();
                break;

            /* copy */
            case SDLK_c:
                break;

            /* paste */
            case SDLK_v:
                break;

            case SDLK_UP:
                console->SetCurrLine(LINE_UP);
                break;

            case SDLK_DOWN:
                console->SetCurrLine(LINE_DOWN);
                break;

            case SDLK_LEFT:
                if (console->cursor > 0)
                {
                    console->cursor--;
                    console->rebuildLine = true;
                }
                break;

            case SDLK_RIGHT:
                if (console->cursor < console->mv_consoleEntries.front().entry.length()) 
                {
                    console->cursor++;
                    console->rebuildLine = true;
                }
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
