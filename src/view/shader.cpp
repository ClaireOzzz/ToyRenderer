#include "shader.h"

unsigned int make_module(const std::string& filepath, unsigned int module_type) {
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while(std::getline(file, line)) {
        bufferedLines << line << '\n';
    }
    std::string shaderSource = bufferedLines.str();
    const char* shaderSrc = shaderSource.c_str();
    // cleanup
    bufferedLines.str("");
    file.close();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
		std::cout << "Shader Module compilation error:\n" << errorLog << std::endl;
	}
    return shaderModule;
}

unsigned int make_shader(const std::string& vertex_filepath, const std::string& frag_filepath) {

    // to store all the shader modules
    std::vector<unsigned int> modules;

    // add a vertex shader module
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    // now frag shader
    modules.push_back(make_module(frag_filepath, GL_FRAGMENT_SHADER));

    // attach the modules
    unsigned int shader = glCreateProgram();
    for (unsigned int shaderMod : modules) {
        glAttachShader(shader, shaderMod);
    }
    // then link the program
    glLinkProgram(shader);

    // debug prints
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
		char errorLog[1024];
		glGetProgramInfoLog(shader, 1024, NULL, errorLog);
		std::cout << "Shader linking error:\n" << errorLog << '\n';
	}

    // free memory
    for (unsigned int shaderModule : modules) {
		glDeleteShader(shaderModule);
	}
    return shader;
}