#pragma once

unsigned int getCurrentShader();
void renderSetup();
void renderScene();
unsigned int gl_alloc(float vertices[], int verticesSize, int sizes[], int sizesLen, int stride);
unsigned int gl_alloc_with_indices(float vertices[], int verticesSize, unsigned int indices[], int indicesSize, int sizes[], int sizesLen, int stride);
unsigned int loadTexture(const char* filePath);
void activateTexture(unsigned int textureID, int textureUnit);
void clearScreen();
