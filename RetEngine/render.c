#include "include.h"
#include "globals.h"
#include "shader.h"
#include "stb/stb_image.h"
#include "render.h"
#include "camera.h"
#include "model.h"

float vertices[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

vec3 cubePositions[] = {
    { 0.0f,  0.0f,  0.0f },
    { 2.0f,  5.0f, -15.0f },
    { -1.5f, -2.2f, -2.5f },
    { -3.8f, -2.0f, -12.3f },
    { 2.4f, -0.4f, -3.5f },
    { -1.7f,  3.0f, -7.5f },
    { 1.3f, -2.0f, -2.5f },
    { 1.5f,  2.0f, -2.5f },
    { 1.5f,  0.2f, -1.5f },
    { -1.3f,  1.0f, -1.5f }
};

unsigned int shaders[] = { 0, 0 };
VertexAttributeObjects vaos;
unsigned int textures[] = { 0, 0 };
unsigned int wallVao;

void drawWalls(); // Delete this, it's just for testing

unsigned int* getShaders() {
    return shaders;
}

void renderSetup() {
    unsigned int shaderTypes[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

    char* shaderPathsDefault[] = { "defaultVertex.glsl", "defaultFragment.glsl" };
    shaders[SHADER_DEFAULT] = compileShaderProgram(shaderPathsDefault, shaderTypes, 2);

    char* shaderPathsLighting[] = { "defaultVertex.glsl", "lightingFragment.glsl" };
    shaders[SHADER_LIGHTING] = compileShaderProgram(shaderPathsLighting, shaderTypes, 2);

    vaos.cube = gl_alloc(vertices, sizeof(vertices), (int[2]){ 3, 2 }, 2, 5);
    vaos.cubelight = gl_alloc(vertices, sizeof(vertices), (int[2]) { 3, 2 }, 2, 5);

    textures[0] = loadTexture("assets\\container.jpg");
    textures[1] = loadTexture("assets\\awesomeface.png");

    for (int i = 0; i < sizeof(textures) / sizeof(textures[0]); i++) {
        char textureName[16];
        sprintf(textureName, "texture%d", i);
        setInt(shaders[SHADER_DEFAULT], textureName, i);
        activateTexture(textures[i], i);
    }

    setFloat(shaders[SHADER_DEFAULT], "mixValue", 0.2f);
    
    //// Delete this, it's just for testing
    //float wallver[] = {
    //    -5.0f,  5.0f, 0.0f,  0.0f, 1.0f,
    //     5.0f,  5.0f, 0.0f,  1.0f, 1.0f,
    //     5.0f, -5.0f, 0.0f,  1.0f, 0.0f,
    //     5.0f, -5.0f, 0.0f,  1.0f, 0.0f,
    //    -5.0f, -5.0f, 0.0f,  0.0f, 0.0f,
    //    -5.0f,  5.0f, 0.0f,  0.0f, 1.0f
    //};

    //// Delete this, it's just for testing
    //wallVao = gl_alloc(wallver, sizeof(wallver), (int[2]){ 3, 2 }, 2, 5);

    updateCamera();
}

void renderScene() {
    setVec3(shaders[SHADER_DEFAULT], "objectColor", (vec3){ 1.0f, 0.5f, 0.31f });
    setVec3(shaders[SHADER_DEFAULT], "lightColor", (vec3){ 1.0f, 1.0f, 1.0f });

    for (int i = 0; i < 10; i++) {
        Model cube = {
			.vertexCount = 36,
			.rotationAxis = { 1.0f, 0.3f, 0.5f },
			.rotationAngle = (float)SDL_GetTicks() / 50 * glm_rad(20.0f * i),
			.scale = { 1.0f, 1.0f, 1.0f }
		};
		glm_vec3_copy(cubePositions[i], cube.position);

		drawModel(cube, shaders[SHADER_DEFAULT], vaos.cube);
    }

    drawModel((Model){
		.vertexCount = 36,
		.position = { 1.2f, 1.0f, 2.0f },
		.rotationAxis = { 0.0f, 0.0f, 0.0f },
		.rotationAngle = 0.0f,
		.scale = { 0.2f, 0.2f, 0.2f }
	}, shaders[SHADER_LIGHTING], vaos.cube);

    //drawWalls();
}

// Delete this, it's just for testing
//void drawWalls() {
//    Model wall = {
//    .vertexCount = 6,
//    .position = { 0.0f, 0.0f, -5.0f },
//    .rotationAxis = { 0.0f, 0.0f, 0.0f },
//    .rotationAngle = 0.0f,
//    .scale = { 1.0f, 1.0f, 1.0f }
//    };
//    drawModel(wall, program, wallVao);
//
//    Model wall2 = {
//       .vertexCount = 6,
//       .position = { 0.0f, 0.0f, 5.0f },
//       .rotationAxis = { 0.0f, 0.0f, 0.0f },
//       .rotationAngle = 0.0f,
//       .scale = { 1.0f, 1.0f, 1.0f }
//    };
//    drawModel(wall2, program, wallVao);
//
//    Model wall3 = {
//       .vertexCount = 6,
//       .position = { -5.0f, 0.0f, 0.0f },
//       .rotationAxis = { 0.0f, 1.0f, 0.0f },
//       .rotationAngle = 90.0f,
//       .scale = { 1.0f, 1.0f, 1.0f }
//    };
//    drawModel(wall3, program, wallVao);
//
//    Model wall4 = {
//       .vertexCount = 6,
//       .position = { 5.0f, 0.0f, 0.0f },
//       .rotationAxis = { 0.0f, 1.0f, 0.0f },
//       .rotationAngle = 90.0f,
//       .scale = { 1.0f, 1.0f, 1.0f }
//    };
//    drawModel(wall4, program, wallVao);
//
//    Model wall5 = {
//       .vertexCount = 6,
//       .position = { 0.0f, -5.0f, 0.0f },
//       .rotationAxis = { 1.0f, 0.0f, 0.0f },
//       .rotationAngle = 90.0f,
//       .scale = { 1.0f, 1.0f, 1.0f }
//    };
//    drawModel(wall5, program, wallVao);
//
//    Model wall6 = {
//       .vertexCount = 6,
//       .position = { 0.0f, 5.0f, 0.0f },
//       .rotationAxis = { 1.0f, 0.0f, 0.0f },
//       .rotationAngle = 90.0f,
//       .scale = { 1.0f, 1.0f, 1.0f }
//    };
//    drawModel(wall6, program, wallVao);
//}

unsigned int newVAO() {
	unsigned int vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	return vertexArrayObject;
}

unsigned int gl_alloc(float vertices[], int verticesSize, int sizes[], int sizesLen, int stride) {
    unsigned int vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    unsigned int offset = 0;
    for (int i = 0; i < sizesLen; i++) {
        glVertexAttribPointer(i, sizes[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset));
        glEnableVertexAttribArray(i);
        offset += sizes[i] * sizeof(float);
    }

    glBindVertexArray(0);

    return vertexArrayObject;
}

unsigned int gl_alloc_with_indices(float vertices[], int verticesSize, unsigned int indices[], int indicesSize, int sizes[], int sizesLen, int stride) {
    // Create and bind the Vertex Array Object (VAO)
    unsigned int vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    // Create and bind the Vertex Buffer Object (VBO)
    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // Create and bind the Element Buffer Object (EBO)
    unsigned int elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    // Set up the vertex attributes
    unsigned int offset = 0;
    for (int i = 0; i < sizesLen; i++) {
        glVertexAttribPointer(i, sizes[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset));
        glEnableVertexAttribArray(i);
        offset += sizes[i] * sizeof(float);
    }

    // Unbind the VAO to prevent accidental modifications
    glBindVertexArray(0);

    // Return the VAO (VBO and EBO are stored within it)
    return vertexArrayObject;
}

unsigned int loadTexture(const char* filePath) {
    // Generate and bind the OpenGL texture
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);// GL_LINEAR_MIPMAP_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load the image using stbi_load
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data) {
        // Determine the image format
        unsigned int format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        // Load the image into the texture
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        // Handle errors
        printf("Failed to load texture: %s\n", filePath);
    }

    // Free the image memory
    stbi_image_free(data);

    return textureID;
}

void activateTexture(unsigned int textureID, int textureUnit) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void clearScreen() {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

