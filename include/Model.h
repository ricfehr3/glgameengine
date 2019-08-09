#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"
class Model
{
public:
    // functions
    Model(const std::string& path)
    {
        loadModel(path);
    }
    void Draw(Shader shader);
private:
    std::vector<Texture> textures_loaded;
    // Model Data
    std::vector<Mesh> meshes;
    std::string directory;
    // Functions
    void loadModel(const std::string& path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif
