#include <Console.h>

#include <Logger.h>

Console::Console()
{
    m_inputReady = false;
    m_show = false;
    mp_shader = new Shader();
    m_bgtexture = 0;
    m_cursortexture = 0;
    
    fontPath = "/usr/share/fonts/truetype/noto/NotoMono-Regular.ttf";
    //fontPath = "fonts/DejaVuSansMono.ttf";
    fontSize = 12;
        
    initFont();
    rebuildLine = true;
    
    _ConsoleEntry consoleEntry {"", 0, 0.0f, 0.0f};
    mv_consoleEntries.insert(mv_consoleEntries.begin(),consoleEntry);
    currLineNum = 0;
    cursor = 0;
}

Console::~Console()
{
    FT_Done_Face(consoleFont.face);
    FT_Done_FreeType(consoleFont.ft);
	glDeleteBuffers(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	
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
        GLOG_ERROR("Freetype failed to init");
        return;
    }
    
    if ((e = FT_New_Face(ft, fontPath.c_str(), 0, &face)))
     {
        GLOG_ERROR("Freetype failed to open font");
        FT_Done_FreeType(ft);
        return;
    }
    
    if (!FT_IS_FIXED_WIDTH(face)) 
    {
        GLOG_ERROR("Font must be fixed width (monospace)!");
        return;
    }
    
    if (!FT_IS_SCALABLE(face)) 
    {
        GLOG_ERROR("Font isn't scalable!");
        return;
    }
    
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    
    if ((e = FT_Load_Glyph(face, FT_Get_Char_Index(face, 'm'), FT_LOAD_RENDER))) 
    {
        GLOG_ERROR("Loading glyphs failed: ");
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
    GLOG_DEBUG("Console font initialized")
}

void Console::init()
{
    getWindowDimensions();
    SDL_AddEventWatch(triggerWatch, this);

    mp_shader->compile("shaders/Console/test.vs", "shaders/Console/test.fs");
    glBindFragDataLocation(mp_shader->ID, 0, "outColor");
    
    glUseProgram(mp_shader->ID);
    
    initGL();
    genConsoleTexture(m_bgtexture);
    genConsoleTexture(m_cursortexture);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    std::cout << "compiled" << std::endl;
    
    glGenTextures(1, &mv_consoleEntries.front().textureID);
    wrap_len = roundf((float)m_winWidth / consoleFont.char_width);
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
        len = DEFAULT_PROMPT_LENGTH + mv_consoleEntries.front().entry.length();
    //}
    //wrap_len = roundf((float)m_winWidth / consoleFont.char_width);

    mv_consoleEntries.front().w = wrap_len * consoleFont.char_width;
    mv_consoleEntries.front().h = (ceil((float)len / (float)wrap_len) + offset) * consoleFont.line_height;

    /* set of `empty' pixels to clear texture */
    unsigned char empty[(int)(mv_consoleEntries.front().w * mv_consoleEntries.front().h)];
    memset(empty, 0, (int)(mv_consoleEntries.front().w * mv_consoleEntries.front().h));

    /* string buffer to output characters from */
    char str[len];
    memset(str, 0, len);
    strcpy(str, DEFAULT_PROMPT);
    strcat(str, mv_consoleEntries.front().entry.c_str());

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
    // cursor's position 
    int cursor_len  = cursor + DEFAULT_PROMPT_LENGTH - 1;
    GLfloat lh = consoleFont.line_height;
    GLfloat cw = consoleFont.char_width;
    // the cursor's length within the line wrapped by max line characters
    GLfloat cx = (float)(cursor_len * consoleFont.char_width);
    // The number of total lines minus the lines of cursor times line height
    GLfloat cy = ((mv_consoleEntries.front().h  / lh) - (float)((cursor_len / wrap_len) + 1)) * lh;
    GLfloat cursor_vert[6][4] = {
        { cx,      cy + lh, 0.0f, 0.0f},
        { cx,      cy,      0.0f, 1.0f},
        { cx + cw, cy,      1.0f, 1.0f},

        { cx,      cy + lh, 0.0f, 0.0f},
        { cx + cw, cy,      1.0f, 1.0f},
        { cx + cw, cy + lh, 1.0f, 0.0f}
    };
    // Draw the cursor 
    glUniform3f(glGetUniformLocation(mp_shader->ID, "textColor"),
            1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, m_cursortexture);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cursor_vert), cursor_vert);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
void Console::initGL()
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

void Console::genConsoleTexture(GLuint &texID)
{
/* figure out the dimensions of the cursor and create pixel */
    unsigned char pixel[1] = { 169 }; // transparency
    /* Generate the texture */
    // todo make a texture class pls
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
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
    rebuildLine = true;
    mv_consoleEntries.front().entry.insert(cursor, 1, *const_cast<char*>(input));
    cursor++;
}

void Console::processEntry()
{
    cursor = 0;
    currLineNum = 0;
    //_ConsoleEntry consoleEntry {"", 0, 0.0f, 0.0f};
    //mv_consoleEntries.insert(mv_consoleEntries.begin(),consoleEntry);
    //glGenTextures(1, &mv_consoleEntries.front().textureID);
    rebuildLine = true;
    m_inputReady = true;
}

void Console::removeLastChar()
{
    if(cursor > 0 && cursor <= mv_consoleEntries.front().entry.length())
    {
        mv_consoleEntries.front().entry.erase(mv_consoleEntries.front().entry.begin() + cursor - 1);
        cursor--;
        rebuildLine = true;
    }
}

void Console::SetCurrLine(ENTRY_DIR dir)
{
    rebuildLine = true;
    bool isClear = false;
    // don't go out of bounds pls
    if(dir == LINE_UP && currLineNum < mv_consoleEntries.size() - 1)
    {
        currLineNum++;
    }
    else if (dir == LINE_DOWN && currLineNum >= 0)
    {
        if (currLineNum == 1)
        {
            cursor = 0;
            isClear = true;
        }
        else
        {
            currLineNum--;
        }
    }
    if (isClear)
    {
        mv_consoleEntries.front().entry = "";
    }
    else
    {
        mv_consoleEntries.front().entry = mv_consoleEntries.at(currLineNum).entry;
    }
    cursor = mv_consoleEntries.front().entry.length();
}

void Console::setOutput(std::string output)
{
    std::cout << "got output: " << output << std::endl;
    _ConsoleEntry consoleEntry {output, 0, 0.0f, 0.0f};
    mv_consoleEntries.insert(mv_consoleEntries.begin(), consoleEntry);
    glGenTextures(1, &mv_consoleEntries.front().textureID);
    updateLineTexture();
    _ConsoleEntry consoleEntryClear {"", 0, 0.0f, 0.0f};
    mv_consoleEntries.insert(mv_consoleEntries.begin(), consoleEntryClear);
    glGenTextures(1, &mv_consoleEntries.front().textureID);
    rebuildLine = true;
}

bool Console::m_show = false;
SDL_mutex* Console::m_mutex = SDL_CreateMutex();

const char    Console::DEFAULT_PROMPT[3]      = "> ";
const int     Console::DEFAULT_PROMPT_LENGTH  = 3;
const int     Console::DEFAULT_LINE_LENGTH    = 128;
const int     Console::DEFAULT_LINE_CHARS     = 256;
const int     Console::CONSOLE_CHARS_LEN      = 128;
