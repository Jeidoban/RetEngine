#include "include.h"
#include "render.h"
#include "shader.h"
#include "camera.h"
#include "globals.h"

vec3 cameraPos = { 0.0f, 0.0f, 3.0f };
vec3 cameraFront = { 0.0f, 0.0f, -1.0f };

void setCameraPosition(vec3 newPosition) {
	glm_vec3_copy(newPosition, cameraPos);
	updateCamera();
}

void addToCameraPosition(vec3 positionToAdd, float multiplier) {
	multiplier *= deltaTime;
	glm_vec3_muladds(positionToAdd, multiplier, cameraPos);
	updateCamera();
}

void getCameraPosition(vec3 cameraPosition) {
	glm_vec3_copy(cameraPos, cameraPosition);
}

void setCameraDirection(vec3 newDirection) {
	glm_vec3_copy(newDirection, cameraFront);
	updateCamera();
}

void getCameraDirection(vec3 cameraDirection) {
	glm_vec3_copy(cameraFront, cameraDirection);
}

void updateCamera() {
	vec3 cameraUp = { 0.0f, 1.0f, 0.0f };
	vec3 cameraTarget;
	glm_vec3_add(cameraPos, cameraFront, cameraTarget);
	mat4 view = GLM_MAT4_IDENTITY_INIT;
	glm_lookat(cameraPos, cameraTarget, cameraUp, view);
	setMat4(getCurrentShader(), "view", view);
}