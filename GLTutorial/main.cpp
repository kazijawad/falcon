#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <vector>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Program.h"
#include "Core/Camera.h"
#include "Core/Model.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

void renderSphere();

// Settings
const unsigned int SOURCE_WIDTH = 800;
const unsigned int SOURCE_HEIGHT = 600;

// Camera
auto camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = (float) SOURCE_WIDTH / 2.0f;
float lastY = (float) SOURCE_HEIGHT / 2.0f;
bool firstMouse = true;

// Clock
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Buffers
unsigned int sphereVAO;
unsigned int indexCount;

int main() {
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(SOURCE_WIDTH, SOURCE_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
        
    // Enable Depth Testing
    glEnable(GL_DEPTH_TEST);
    
    // Compile Shader(s)
    auto program = Program("Programs/pbr.vs", "Programs/pbr.fs");
    
    program.use();
    program.setVec3("albedo", 0.5f, 0.0f, 0.0f);
    program.setFloat("ao", 1.0f);
    
    // Lighting
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f,  10.0f, 10.0f),
        glm::vec3( 10.0f,  10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3( 10.0f, -10.0f, 10.0f),
    };

    glm::vec3 lightColors[] = {
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)
    };

    int numRows = 7;
    int numColumns = 7;
    float spacing = 2.5;
    
    // Static Program Uniforms
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SOURCE_WIDTH / (float) SOURCE_HEIGHT, 0.1f, 100.0f);
    program.use();
    program.setMat4("projection", projection);
    
    // Render Loop
    while (!glfwWindowShouldClose(window)) {
        // Per-Frame Time
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Input
        processInput(window);
        
        // Scene Cleanup
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Dynamic Program Uniforms
        auto view = camera.GetViewMatrix();
        program.use();
        program.setMat4("view", view);
        program.setVec3("cameraPosition", camera.Position);
        
        // Render Spheres
        auto model = glm::mat4(1.0f);
        for (unsigned int row = 0; row < numRows; ++row) {
            program.setFloat("metallic", (float) row / (float) numRows);
            for (unsigned int col = 0; col < numColumns; ++col) {
                program.setFloat("roughness", glm::clamp((float) col / (float) numColumns, 0.05f, 1.0f));
                
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(
                    (col - (numColumns / 2)) * spacing,
                    (row - (numRows /2)) * spacing,
                    0.0f
                ));
                program.setMat4("model", model);
                renderSphere();
            }
        }
        
        // Render Lights
        for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i) {
            glm::vec3 newPosition = lightPositions[i];
            program.setVec3("lightPositions[" + std::to_string(i) + "]", newPosition);
            program.setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
            
            model = glm::mat4(1.0f);
            model = glm::translate(model, newPosition);
            model = glm::scale(model, glm::vec3(0.5f));
            program.setMat4("model", model);
            renderSphere();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void renderSphere() {
    if (!sphereVAO) {
        glGenVertexArrays(1, &sphereVAO);
        
        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;
        
        const unsigned int xSegments = 64;
        const unsigned int ySegments = 64;
        const float PI = 3.14159265359f;
        for (unsigned int x = 0; x < xSegments; ++x) {
            for (unsigned int y = 0; y <ySegments; ++y) {
                float xSegment = (float) x / (float) xSegments;
                float ySegment = (float) y / (float) ySegments;
                
                float xPosition = std::cos(xSegments * 2.0f * PI) * std::sin(ySegments * PI);
                float yPosition = std::cos(ySegments * PI);
                float zPosition = std::sin(xSegments * 2.0f * PI) * std::sin(ySegments * PI);
                
                positions.push_back(glm::vec3(xPosition, yPosition, zPosition));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPosition, yPosition, zPosition));
            }
        }
        
        bool oddRow = false;
        for (unsigned int y = 0; y < ySegments; ++y) {
            if (!oddRow) {
                for (unsigned int x = 0; x <= xSegments; ++x) {
                    indices.push_back(y * (xSegments + 1) + x);
                    indices.push_back((y + 1) * (xSegments + 1) + x);
                }
            } else {
                for (unsigned int x = xSegments; x >= 0; --x) {
                    indices.push_back((y + 1) * (xSegments + 1) + x);
                    indices.push_back(y * (xSegments + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = static_cast<unsigned int>(indices.size());
        
        std::vector<float> data;
        for (unsigned int i = 0; i < positions.size(); ++i) {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);
            if (normals.size() > 0) {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
            if (uv.size() > 0) {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }
        }
        
        glBindVertexArray(sphereVAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        
        unsigned int stride = (3 + 2 + 3) * sizeof(float);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*) 0);
        
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*) (3 * sizeof(float)));
        
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*) (6 * sizeof(float)));
    }
    
    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xOffset, yOffset);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}

unsigned int loadTexture(const char* path) {
    std::string filename = std::string(path);
    
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, numComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &numComponents, 0);
    if (data) {
        GLenum format = GL_RED;
        if (numComponents == 3) {
            format = GL_RGB;
        } else if (numComponents == 4) {
            format = GL_RGBA;
        }
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        GLenum wrap = GL_REPEAT;
        if (format == GL_RGBA) {
            wrap = GL_CLAMP_TO_EDGE;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        std::cout << "ERROR::MODEL::TEXTURE::LOAD_FAILED::" << path << std::endl;
    }
    
    stbi_image_free(data);
    
    return textureID;
}
