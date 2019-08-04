#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    // Mesh Data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    // functions
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>, std::vector<Texture> textures);
    void Draw(Shader shader);
private:
    // Render data
    unsigned int VAO, VBO, EBO;
    // functions
    void setupMesh();
};

#endif
