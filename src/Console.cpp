#include <Console.h>

Console::Console()
{
    m_inputReady = false;
    m_show = false;
    mp_shader = new Shader();
    m_bgtexture = -1; // maybe a bad init
    
    fontPath = "/usr/share/fonts/truetype/noto/NotoMono-Regular.ttf";
    //fontPath = "fonts/DejaVuSansMono.ttf";
    fontSize = 12;
        
    initFont();
    rebuildLine = true;
    
    _ConsoleEntry consoleEntry {"", 0, 0.0f, 0.0f};
    mv_consoleEntries.insert(mv_consoleEntries.begin(),consoleEntry);
    currLineNum = 0;
}

void Console::setWindow(SDL_Window* window)
{
    mp_window = window;
}

void Console::getWindowDimensions()
{
    SDL_GetWindowSize(mp_window, &m_winWidth, &m_winHeight);
}

bool Console::inputReady()
{
    bool ret = false;
    if(m_inputReady)
    {
        m_inputReady = false;
        ret = true;
    }
    
    return ret;
}

std::string Console::getInput()
{
    return mv_consoleEntries.front().entry;
}

void Console::initFont()
{
    FT_Library ft;
    FT_Face face;
    FT_Error e;
    
    if ((e = FT_Init_FreeType(&ft)))
     {
        std::cout << "Freetype failed to init" << std::endl;
        return;
    }
    
    if ((e = FT_New_Face(ft, fontPath.c_str(), 0, &face)))
     {
        std::cout << "Freetype failed to open font" << std::endl;
        FT_Done_FreeType(ft);
        return;
    }
    
    if (!FT_IS_FIXED_WIDTH(face)) 
    {
        std::cout << "Font must be fixed width (monospace)!" << std::endl;
        return;
    }
    
    if (!FT_IS_SCALABLE(face)) 
    {
        std::cout << "Font isn't scalable!" << std::endl;
        return;
    }
    
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    
    if ((e = FT_Load_Glyph(face, FT_Get_Char_Index(face, 'm'), FT_LOAD_RENDER))) 
    {
        std::cout << "Loading glyphs failed: " << std::endl;
        return;
    }
    
    /* `>> 6' adjusts values which are based at 1/64th of screen pixel size */
    consoleFont.face = face;
    consoleFont.ft = ft;
    consoleFont.font_size = fontSize;
    consoleFont.advance = (face->glyph->metrics.horiAdvance >> 6);
    consoleFont.char_width = 
        (face->glyph->metrics.horiBearingX + face->glyph->metrics.width) >> 6;
    consoleFont.line_height = 
          (FT_MulFix(face->ascender, face->size->metrics.y_scale) >> 6)
        - (FT_MulFix(face->descender, face->size->metrics.y_scale) >> 6)
        + 1;
    consoleFont.baseline = abs(face->descender) * fontSize / face->units_per_EM;
}

void Console::init()
{
    getWindowDimensions();
    SDL_AddEventWatch(triggerWatch, this);

    mp_shader->compile("shaders/Console/test.vs", "shaders/Console/test.fs");
    glBindFragDataLocation(mp_shader->ID, 0, "outColor");
    
    glUseProgram(mp_shader->ID);
    
    
    genBackgroundGL();
    genBackgroundTexture();
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    std::cout << "compiled" << std::endl;
    
    glGenTextures(1, &m_lineTexture);
}

void Console::draw()
{
    if(m_show)
    {
        if (rebuildLine) 
        {
            rebuildLine = false;
            if (updateLineTexture())
            {
                return;
            }
        }
        
        glDepthMask(GL_FALSE);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        mp_shader->use();
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, 
                sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glActiveTexture(GL_TEXTURE0);
        
        renderBackground();
        renderLines();
        renderCursor();
        
        /* unset all of the set we set  */
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);
        glDisable(GL_BLEND);
        glDisable(GL_CULL_FACE);
        glDepthMask(GL_TRUE);
    }
}

int Console::updateLineTexture()
{
    GLfloat advance = consoleFont.char_width;
    GLfloat x = 0.0f;
    GLfloat y = 0.0f;
    float offset = 0.0f;
    int len = 0;
    
    //if (line->output) 
    //{
    //    /* +1 for the newline character inserted as sentinel */
    //    len = DEFAULT_PROMPT_LEN + line->len + 1 + strlen(line->output);
    //    /* again +1.0f for newline */
    //    offset = 1.0f;
    //} 
    //else 
    //{
        len = DEFAULT_PROMPT_LENGTH + currentLine.length();
    //}
    int wrap_len = roundf((float)m_winWidth / consoleFont.char_width);

    mv_consoleEntries.front().w = wrap_len * consoleFont.char_width;
    mv_consoleEntries.front().h = (ceil((float)len / (float)wrap_len) + offset) * consoleFont.line_height;

    /* set of `empty' pixels to clear texture */
    unsigned char empty[(int)(mv_consoleEntries.front().w * mv_consoleEntries.front().h)];
    memset(empty, 0, (int)(mv_consoleEntries.front().w * mv_consoleEntries.front().h));

    /* string buffer to output characters from */
    char str[len];
    memset(str, 0, len);
    strcpy(str, DEFAULT_PROMPT);
    strcat(str, currentLine.c_str());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mv_consoleEntries.front().textureID);

    /* Resize the texture if needed and set any attributes */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 
            mv_consoleEntries.front().w, mv_consoleEntries.front().h, 
            0, GL_RED, GL_UNSIGNED_BYTE, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Clear the texture */
    glTexSubImage2D(GL_TEXTURE_2D, 
            0, 0, 0, mv_consoleEntries.front().w, mv_consoleEntries.front().h, 
            GL_RED, GL_UNSIGNED_BYTE, empty);

    for (int i = 0; i < len; i++) {
        if (FT_Load_Char(consoleFont.face, str[i], FT_LOAD_RENDER))
            continue;

        GLfloat bearingY = consoleFont.face->glyph->bitmap_top;

        if (x + advance > mv_consoleEntries.front().w || str[i] == '\n') {
            y += consoleFont.line_height;
            x = 0.0f;

            if (str[i] == '\n')
                continue;
        }

        if (str[i] == ' ')
        {
            x += advance;
        }
        else
        {
            /*
             * Every character has a different bearing. To account for that we use
             * the current line (y) and add in the line height as a buffer. In that
             * buffer can each character be placed at different y values so they
             * all appear in the same baseline.
             */
            GLfloat ypos = y + consoleFont.line_height - bearingY - consoleFont.baseline - 1.0f;

            /*
             * We also make sure to use SubImage here because we're actually 
             * appending to the previously created texture.
             */
            glTexSubImage2D(
                GL_TEXTURE_2D, 
                0, 
                x, 
                ypos,
                consoleFont.face->glyph->bitmap.width,
                consoleFont.face->glyph->bitmap.rows,
                GL_RED,
                GL_UNSIGNED_BYTE, 
                consoleFont.face->glyph->bitmap.buffer
            );
            x += advance;
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    return 0;
}

void Console::renderBackground()
{    
    GLfloat xpos = 0.0f;
    GLfloat ypos = 0.0f;
    GLfloat ww   = (float)m_winWidth;
    GLfloat wh   = (float)m_winHeight;
    GLfloat vertices[6][4] = {
        { xpos,      ypos + wh, 0.0f, 0.0f},
        { xpos,      ypos,      0.0f, 1.0f},
        { xpos + ww, ypos,      1.0f, 1.0f},
                                         
        { xpos,      ypos + wh, 0.0f, 0.0f},
        { xpos + ww, ypos,      1.0f, 1.0f},
        { xpos + ww, ypos + wh, 1.0f, 0.0f}
    };

    glUniform3f(glGetUniformLocation(mp_shader->ID, "textColor"),
        0.0f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, m_bgtexture);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Console::renderLines()
{
    GLfloat xpos = 0.0f;
    GLfloat ypos = 0.0f;
    glUniform3f(glGetUniformLocation(mp_shader->ID, "textColor"), 1.0f, 1.0f, 1.0f);
    for (auto&& entry: mv_consoleEntries)
    {   
        GLfloat vertices[6][4] = 
        {
            { xpos,           ypos + entry.h, 0.0f, 0.0f},
            { xpos,           ypos,           0.0f, 1.0f},
            { xpos + entry.w, ypos,           1.0f, 1.0f},
                                             
            { xpos,           ypos + entry.h, 0.0f, 0.0f},
            { xpos + entry.w, ypos,           1.0f, 1.0f},
            { xpos + entry.w, ypos + entry.h, 1.0f, 0.0f}
        };
        
        glBindTexture(GL_TEXTURE_2D, entry.textureID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        ypos += entry.h;
    }
}

void Console::renderCursor()
{

}

void Console::genCursorGL()
{

}

void Console::genBackgroundGL()
{
    glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	mp_shader->use();
	glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    
    GLint posAttrib = glGetAttribLocation(mp_shader->ID, "vertex");
    glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(posAttrib);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);
    
    /* Set color for fragment shader */
    glUniform3f(glGetUniformLocation(mp_shader->ID, "textColor"),
            1.0f, 1.0f, 1.0f);
    
    GLfloat l = 0.0f;
    GLfloat r = (float)m_winWidth;
    GLfloat b = 0.0f;
    GLfloat t = (float)m_winHeight;
    GLfloat orthoMatrix[4*4] = {
        2.0f / (r - l),   0.0f,             0.0f, 0.0f,
        0.0f,             2.0f / (t - b),   0.0f, 0.0f,
        0.0f,             0.0f,            -1.0f, 0.0f,
        -(r + l)/(r - l), -(t + b)/(t - b), 0.0f, 1.0f,
    };
    glUniformMatrix4fv(glGetUniformLocation(mp_shader->ID, "projection"),
            1, GL_FALSE, orthoMatrix);
    
}

void Console::genBackgroundTexture()
{
/* figure out the dimensions of the cursor and create pixel */
    unsigned char pixel[1] = { 169 }; // transparency
    /* Generate the texture */
    // todo make a texture class pls
    glGenTextures(1, &m_bgtexture);
    glBindTexture(GL_TEXTURE_2D, m_bgtexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1, 1, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri
    (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexSubImage2D(
            GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RED, GL_UNSIGNED_BYTE, pixel);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Console::getInput(const char* input)
{
    currentLine += input;
    rebuildLine = true;
}

void Console::processEntry()
{
    currLineNum = 0;
    _ConsoleEntry consoleEntry {currentLine, m_lineTexture, w, h};
    glGenTextures(1, &m_lineTexture);
    mv_consoleEntries.insert(mv_consoleEntries.begin(),consoleEntry);
    currentLine.clear();
    rebuildLine = true;
    m_inputReady = true;
}

void Console::removeLastChar()
{
    if(currentLine.size() != 0)
    {
        currentLine.resize(currentLine.size() - 1);
        rebuildLine = true;
    }
}

void Console::SetCurrLine(ENTRY_DIR dir)
{
    rebuildLine = true;
    std::cout << currLineNum << " " << mv_consoleEntries.size() << std::endl;
    currentLine = mv_consoleEntries.at(currLineNum).entry;
    // don't go out of bounds pls
    if(dir == LINE_UP && currLineNum < mv_consoleEntries.size() - 1)
    {
        currLineNum++;
    }
    else if (dir == LINE_DOWN && currLineNum > 0)
    {
        currLineNum--;
    }
    // clear line if at bottom at array
    else if (dir == LINE_DOWN)
    {
        currentLine = "";
    }
}

bool Console::m_show = false;
SDL_mutex* Console::m_mutex = SDL_CreateMutex();

const char    Console::DEFAULT_PROMPT[3]      = "> ";
const int     Console::DEFAULT_PROMPT_LENGTH  = 3;
const int     Console::DEFAULT_LINE_LENGTH    = 128;
const int     Console::DEFAULT_LINE_CHARS     = 256;
const int     Console::CONSOLE_CHARS_LEN      = 128;
