#ifndef model_h
#define model_h

#include <string>
#include <vector>

#include <assimp/scene.h>
#include <poly/program.h>
#include <poly/mesh.h>

namespace poly {

unsigned int TextureFromFile(const char* path, const std::string &directory);

class Model {
public:
    Model(const char* path);

    void Draw(Program program);

private:
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
    std::string directory;

    void loadModel(std::string path);

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

}

#endif
