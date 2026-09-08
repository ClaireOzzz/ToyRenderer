#pragma once
#include "../config.h"

class OBJMesh {
public:
    OBJMesh(glm::vec3 position, glm::vec3 euler, const std::string& filepath);
    ~OBJMesh();
    void draw();

private:
    unsigned int VAO, VBO;
    
    void make_mesh(float l, float w, float h);
    void make_obj_mesh(glm::vec3 position, glm::vec3 euler, const std::string& filepath);

    glm::vec2 read_vec2(std::vector<std::string> words);
    glm::vec3 read_vec3(std::vector<std::string> words);
    
    glm::vec3 read_face(std::vector<std::string> words, 
        std::vector<glm::vec3>& v, 
        std::vector<glm::vec2>& vt,
        std::vector<glm::vec3>& vn,
        std::vector<float>& vertices);
    glm::vec3 read_corner(std::string description, // 128/167/128 = 1 description
        std::vector<glm::vec3>& v, 
        std::vector<glm::vec2>& vt,
        std::vector<glm::vec3>& vn,
        std::vector<float>& vertices);


};