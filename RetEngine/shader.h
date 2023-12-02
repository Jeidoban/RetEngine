#pragma once

#include <stdbool.h>

unsigned int compileShaderProgram(const char* shaderPaths[], unsigned int shaderTypes[], int numShaders);
void useShader(unsigned int shaderProgram);
void setBool(unsigned int shaderProgram, const char* name, bool value);
void setInt(unsigned int shaderProgram, const char* name, int value);
void setFloat(unsigned int shaderProgram, const char* name, float value);
void setMat4(unsigned int shaderProgram, const char* name, mat4 value);
