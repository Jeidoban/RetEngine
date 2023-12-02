#include "include.h"
#include "globals.h"
#include "input.h"
#include "camera.h"

void handleEvents() {
	handleMouseEvents();
	handleKeyboardEvents();

	SDL_Keycode key;
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			key = event.key.keysym.sym;

			if (key == SDLK_ESCAPE) {
				running = false;
			}
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				screenWidth = event.window.data1;
				screenHeight = event.window.data2;
				glViewport(0, 0, screenWidth, screenHeight);
			}
			break;
			// Other cases can be added here as needed
		}
	}
}

float yaw = -90.0f;
float pitch = 0.0f;
void handleMouseEvents() {
	int xpos, ypos;
	SDL_GetRelativeMouseState(&xpos, &ypos);

	float xoffset = xpos;
	float yoffset = -ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	vec3 direction;
	direction[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
	direction[1] = sin(glm_rad(pitch));
	direction[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
	glm_normalize(direction);
	setCameraDirection(direction);
}

static void moveDirection(float cameraSpeed, bool forward) {
	vec3 cam;
	getCameraDirection(cam);

	if (!forward) {
		vec3 right;
		glm_vec3_crossn(cam, (vec3) { 0.0f, 1.0f, 0.0f }, right);
		addToCameraPosition(right, cameraSpeed);
		return;
	}

	cam[1] = 0.0f;
	glm_normalize(cam);
	addToCameraPosition(cam, cameraSpeed);
}

void handleKeyboardEvents() {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	const float cameraSpeed = 0.005f;

	if (keystate[SDL_SCANCODE_W]) {
		moveDirection(cameraSpeed, true);
	}
	else if (keystate[SDL_SCANCODE_S]) {
		moveDirection(-cameraSpeed, true);
	}
	else if (keystate[SDL_SCANCODE_A]) {
		moveDirection(-cameraSpeed, false);
	}
	else if (keystate[SDL_SCANCODE_D]) {
		moveDirection(cameraSpeed, false);
	}

}