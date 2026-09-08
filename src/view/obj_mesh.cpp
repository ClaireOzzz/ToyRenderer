#include "obj_mesh.h"

OBJMesh::OBJMesh(glm::vec3 position, glm::vec3 euler, const std::string& filepath) {
    make_obj_mesh(position, euler, filepath);
}

void OBJMesh::make_obj_mesh(glm::vec3 position, glm::vec3 euler, const std::string& filepath) {
    std::vector<glm::vec3> v;
    std::vector<glm::vec2> vt;
    std::vector<glm::vec3> vn;
    std::vector<glm::vec3> f;
    std::vector<float> vertices;

    // 2 passes on file: 1. to know the size 2. reading (to avoid dynamic resizing)
    size_t vertexCount = 0;
    size_t texCoordCount = 0;
    size_t normalCount = 0;
    size_t triangleCount = 0;

    std::string line;
    std::vector<std::string> words;
    std::vector<std::string> f_words;

    std::ifstream file;
    file.open(filepath);
    while (std::getline(file, line)) {
        words = split(line, " "); // all parts now in vector

        if (words[0] == "v") {
            ++vertexCount;
        }
        else if (words[0] == "vn") {
            ++normalCount;
        }
        else if (words[0] == "vt") {
            ++texCoordCount;
        }
        else if (words[0] == "f") {
            triangleCount += words.size() - 3;
        }
    }
    file.close();

    v.reserve(vertexCount);
    vn.reserve(normalCount);
    vt.reserve(texCoordCount);
    vertices.reserve(triangleCount * 3 * 8); // each triangle has 3 corners, 8 floats (3 for pos, 2 for texcoord, 3 for norm)

    file.open(filepath);
    while (std::getline(file, line)) {
        words = split(line, " "); // all parts now in vector

        if (words[0] == "v") {
            v.push_back(read_vec3(words));
        }
        else if (words[0] == "vn") {
            vn.push_back(read_vec3(words));
        }
        else if (words[0] == "vt") {
            vt.push_back(read_vec2(words));
        }
        
        else if (words[0] == "f") {
            read_face(words, v, vt, vn, vertices);
        }
    }
    file.close();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                    vertices.data(), GL_STATIC_DRAW );
    
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);
    glEnableVertexAttribArray(0);

    //texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12); // offset = 12 bytes
    glEnableVertexAttribArray(1);
}

glm::vec2 OBJMesh::read_vec2(std::vector<std::string> words) {
    return glm::vec2(std::stof(words[1]), std::stof(words[2]));
}

glm::vec3 OBJMesh::read_vec3(std::vector<std::string> words) {
    return glm::vec3(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));
}

glm::vec3 OBJMesh::read_face(std::vector<std::string> words, 
        std::vector<glm::vec3>& v, 
        std::vector<glm::vec2>& vt,
        std::vector<glm::vec3>& vn,
        std::vector<float>& vertices) {
    
    size_t triCount = words.size() -3;

    for (size_t i = 0; i < triCount; ++i) {
        // read corner 1
        read_corner(words[1], v, vt, vn, vertices);
        read_corner(words[2+i], v, vt, vn, vertices);
        read_corner(words[3+i], v, vt, vn, vertices);
    }
}

glm::vec3 OBJMesh::read_corner(std::string description, 
        std::vector<glm::vec3>& v, 
        std::vector<glm::vec2>& vt,
        std::vector<glm::vec3>& vn,
        std::vector<float>& vertices) {
    
    std::vector<std::string> v_vt_vn = split(description, "/");

    // position
    glm::vec3 pos = v[std::stol(v_vt_vn[0]) - 1];
    vertices.push_back(pos[0]);
    vertices.push_back(pos[1]);
    vertices.push_back(pos[2]);
    // tex coord
    glm::vec2 tex = vt[std::stol(v_vt_vn[1]) - 1];
    vertices.push_back(tex[0]);
    vertices.push_back(tex[1]);
    vertices.push_back(tex[2]);
    // normals
    glm::vec3 normal = vn[std::stol(v_vt_vn[2]) - 1];
    vertices.push_back(normal[0]);
    vertices.push_back(normal[1]);
    vertices.push_back(normal[2]);
}

void OBJMesh::draw() {
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

OBJMesh::~OBJMesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}