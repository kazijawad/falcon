#ifndef mesh_h
#define mesh_h

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <poly/core/program.h>

namespace poly {

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Draw(Program &program);

private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

}

#endif
