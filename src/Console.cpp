#include <Console.h>

Console::Console()
{
    m_show = false;
    mp_bgshader = new Shader();
    m_bgtexture = -1; // maybe a bad init
}

void Console::init()
{
    SDL_AddEventWatch(triggerWatch, this);
    //SDL_AddEventWatch(forwardTriggerWatch, NULL);

    mp_bgshader->compile("shaders/Console/test.vs", "shaders/Console/test.fs");
    glBindFragDataLocation(mp_bgshader->ID, 0, "outColor");
    
    glUseProgram(mp_bgshader->ID);
    
    
    genBackgroundGL();
    genBackgroundTexture();
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    std::cout << "compiled" << std::endl;
    
    //glUniform3f(glGetUniformLocation(mp_bgshader->ID, "textColor"),
     //       1.0f, 1.0f, 1.0f);
    
    //genBackgroundTexture();
}

void Console::draw()
{
    if(m_show)
    {
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        renderBackground();
        renderCursor();
        
        /* unset all of the set we set  */
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);
        glDisable(GL_BLEND);
        glDisable(GL_CULL_FACE);
    }
}

void Console::renderBackground()
{    
    GLfloat xpos = 0.0f;
    GLfloat ypos = 0.0f;
    GLfloat ww   = 800.0f;//tty->window_width;
    GLfloat wh   = 600.0f;//tty->window_height;
    GLfloat vertices[6][4] = {
        { xpos,      ypos + wh, 0.0f, 0.0f},
        { xpos,      ypos,      0.0f, 1.0f},
        { xpos + ww, ypos,      1.0f, 1.0f},
                                         
        { xpos,      ypos + wh, 0.0f, 0.0f},
        { xpos + ww, ypos,      1.0f, 1.0f},
        { xpos + ww, ypos + wh, 1.0f, 0.0f}
    };

    mp_bgshader->use();
    glBindVertexArray(m_bgVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_bgVBO);

    glBufferData(GL_ARRAY_BUFFER, 
            sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glActiveTexture(GL_TEXTURE0);
    
    
    
    glUniform3f(glGetUniformLocation(mp_bgshader->ID, "textColor"),
        0.0f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, m_bgtexture);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Console::renderCursor()
{

}

void Console::genCursorGL()
{

}

void Console::genBackgroundGL()
{
    //float vertices[] = {
    //    // positions          // texture coords
    //    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // bottom left  
    //     1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // bottom right 
    //    -1.0f,  1.0f, 0.0f,   0.0f, 1.0f, // top left
    //     1.0f,  1.0f, 0.0f,   1.0f, 1.0f  // top right
    //};
    
    //unsigned int indices[] = {  
    //    0, 1, 2, // first triangle
    //    2, 1, 3 // first triangle
    //};
    
    glGenVertexArrays(1, &m_bgVAO);
	glGenBuffers(1, &m_bgVBO);
	//glGenBuffers(1, &m_bgEBO);
	mp_bgshader->use();
	glBindVertexArray(m_bgVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_bgVBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bgEBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // position
    GLint posAttrib = glGetAttribLocation(mp_bgshader->ID, "vertex");
    glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(posAttrib);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);
    
    /* Set color for fragment shader */
    glUniform3f(glGetUniformLocation(mp_bgshader->ID, "textColor"),
            1.0f, 1.0f, 1.0f);
    
    GLfloat l = 0.0f;
    GLfloat r = 800.0f;//(GLfloat)tty->window_width;
    GLfloat b = 0.0f;
    GLfloat t = 600.0f;//(GLfloat)tty->window_height;
    GLfloat orthoMatrix[4*4] = {
        2.0f / (r - l),   0.0f,             0.0f, 0.0f,
        0.0f,             2.0f / (t - b),   0.0f, 0.0f,
        0.0f,             0.0f,            -1.0f, 0.0f,
        -(r + l)/(r - l), -(t + b)/(t - b), 0.0f, 1.0f,
    };
    glUniformMatrix4fv(glGetUniformLocation(mp_bgshader->ID, "projection"),
            1, GL_FALSE, orthoMatrix);
    
    //glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    // texture coord attribute
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /* fill it with the pixel */
    glTexSubImage2D(
            GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RED, GL_UNSIGNED_BYTE, pixel);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Console::getInput(const char* input)
{
    currentLine += input;
    std::cout << currentLine << std::endl;
}

void Console::clearLine()
{
    currentLine.clear();
}

void Console::removeLastChar()
{
    currentLine.resize(currentLine.size() - 1);
}

bool Console::m_show = false;
SDL_mutex* Console::m_mutex = SDL_CreateMutex();
