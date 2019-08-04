#include "glad/glad.h"
#include "stb_image.h"
#include "Shader.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <unistd.h>

void framebuffer_size_callback(GLFWwindow* window, int winwidth, int winheight);

int win_width = 800;
int win_height = 600;

float smileStrength = 0.2;
float smileScalar   = 0.001;

float vertRectTex[] = 
{
	// positions              // colors                // texture coords
     0.5f,  0.5f,  0.0f,      1.0f,  0.0f,  0.0f,      1.0f,  1.0f,  // top right
     0.5f, -0.5f,  0.0f,      0.0f,  1.0f,  0.0f,      1.0f,  0.0f,  // bottom right
    -0.5f, -0.5f,  0.0f,      0.0f,  0.0f,  1.0f,      0.0f,  0.0f,  // bottom left
    -0.5f,  0.5f,  0.0f,      1.0f,  1.0f,  0.0f,      0.0f,  1.0f   // top left
};

unsigned int indices[] =
{
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

void processInput(GLFWwindow *window);

int main (int argc, char** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(win_width, win_height, "Shid and Fardt", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

	glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	//glViewport(0,0,win_width,win_height);

	Shader ourShader("src/shaders/4.1.texture.vs", "src/shaders/4.1.texture.fs");

	unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertRectTex), vertRectTex, GL_STATIC_DRAW);    

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);    

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);	
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);	
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
 
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// TEXTURES!!!!
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	stbi_set_flip_vertically_on_load(true);
	unsigned int woodTexture, awesomeTexture;
	glGenTextures(1, &woodTexture);
	glBindTexture(GL_TEXTURE_2D, woodTexture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &awesomeTexture);
	glBindTexture(GL_TEXTURE_2D, awesomeTexture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use(); // Activate shader before setting uniforms, fucker
	ourShader.setInt("woodTexture", 0);
	ourShader.setInt("awesomeTexture", 1);

    while(!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    
		// assign texture unit
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, awesomeTexture);

		ourShader.setFloat("bigSmile", smileStrength);        

		ourShader.use();	
		glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        

		glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
        glfwSetWindowShouldClose(window, true);
	}	
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{    
		smileStrength -= smileScalar;
	}	
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{     
		smileStrength += smileScalar;
	}
	std::cout << smileStrength << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int winwidth, int winheight)
{   
    win_width = winwidth;
    win_height = winheight;
    glViewport(0, 0, win_width, win_height);
}
