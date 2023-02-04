#include <filesystem>
#include <fstream>
#include <sstream>

#include <polyhedron/core/material.h>
#include <polyhedron/core/renderer.h>

namespace polyhedron {

Material::Material(const std::string &vertexPath, const std::string &fragmentPath) {
    std::ifstream vertexStream(vertexPath);
    if (!vertexStream.is_open()) {
        std::printf("Failed to read vertex shader: %s\n", vertexPath.c_str());
    }

    std::ifstream fragmentStream(fragmentPath);
    if (!fragmentStream.is_open()) {
        std::printf("Failed to read fragment shader: %s\n", fragmentPath.c_str());
    }

    std::string vertexCode((std::istreambuf_iterator<char>(vertexStream)), std::istreambuf_iterator<char>());
    std::string fragmentCode((std::istreambuf_iterator<char>(fragmentStream)), std::istreambuf_iterator<char>());

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    int success = 0;
    char infoLog[512];

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::printf("Failed to compile vertex shader: %s\n", infoLog);
    }

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::printf("Failed to compile fragment shader: %s\n", infoLog);
    }

    id = glCreateProgram();

    glAttachShader(id, vertex);
    glAttachShader(id, fragment);

    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::printf("Failed to link program: %s\n", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
};

void Material::use(RenderState &state) {
    glUseProgram(id);
}

void Material::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Material::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Material::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Material::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void Material::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

void Material::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void Material::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Material::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void Material::setVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void Material::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Material::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Material::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

}
