#pragma once

#define SHADER_DEFAULT 0
#define SHADER_LIGHTING 1
#define NUM_SHADERS 2

typedef struct {
	unsigned int cube;
	unsigned int cubelight;
} VertexAttributeObjects;

unsigned int* getShaders();
void renderSetup();
void renderScene();
unsigned int newVAO();
unsigned int gl_alloc(float vertices[], int verticesSize, int sizes[], int sizesLen, int stride);
unsigned int gl_alloc_with_indices(float vertices[], int verticesSize, unsigned int indices[], int indicesSize, int sizes[], int sizesLen, int stride);
unsigned int loadTexture(const char* filePath);
void activateTexture(unsigned int textureID, int textureUnit);
void clearScreen();
