#pragma once

typedef struct {
	int vertexCount;
	vec3 position;
	vec3 rotationAxis;
	float rotationAngle;
	vec3 scale;
} Model;

void drawModel(Model model, unsigned int shader, unsigned int VAO);


