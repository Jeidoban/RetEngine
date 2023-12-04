#include "include.h"
#include "shader.h"

unsigned int compileShaderProgram(const char* shaderPaths[], unsigned int shaderTypes[], int numShaders) {
    unsigned int* shaders = malloc(sizeof(unsigned int) * numShaders);

    for (int i = 0; i < numShaders; i++) {
        FILE* file;
        char* buffer;

        fopen_s(&file, shaderPaths[i], "rb");

        if (file == NULL) {
            printf("Failed to open the file: %s\n", shaderPaths[i]);
            free(shaders);
            return 0;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        buffer = malloc(fileSize + 1);
        fread(buffer, fileSize, 1, file);
        buffer[fileSize] = '\0';

        fclose(file);

        unsigned int shader = glCreateShader(shaderTypes[i]);
        glShaderSource(shader, 1, &buffer, NULL);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);

            free(buffer);
            free(shaders);
            return 0;
        }

        shaders[i] = shader;
        free(buffer);
    }

    unsigned int shaderProgram = glCreateProgram();

    for (int i = 0; i < numShaders; i++) {
        glAttachShader(shaderProgram, shaders[i]);
    }

    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    for (int i = 0; i < numShaders; i++) {
        glDeleteShader(shaders[i]);
    }

    free(shaders);
    return shaderProgram;
}

void useShader(unsigned int shaderProgram) {
	glUseProgram(shaderProgram);
}

void setBool(unsigned int shaderProgram, const char* name, bool value) {
    useShader(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, name), (int)value);
}

void setInt(unsigned int shaderProgram, const char* name, int value) {
    useShader(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void setFloat(unsigned int shaderProgram, const char* name, float value) {
	useShader(shaderProgram);
	glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void setMat4(unsigned int shaderProgram, const char* name, mat4 value) {
    useShader(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, value);
}

void setVec3(unsigned int shaderProgram, const char* name, vec3 value) {
    useShader(shaderProgram);
	glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, value);
}
