#include "include.h"
#include "render.h"
#include "input.h"

SDL_Window* window;
SDL_GLContext glContext;

Uint64 deltaTime = 0;
bool running = true;
int screenWidth = 800;
int screenHeight = 600;

void initWindow(const int width, const int height);
void deleteWindow();
void setFPS(int fps);

int main(int argc, char* args[]) {
	initWindow(800, 600);
	renderSetup();

	while (running) {
		setFPS(120);
		handleEvents();
		clearScreen();

		renderScene();

		SDL_GL_SwapWindow(window);
	}

	deleteWindow();
	return 0;
}

Uint64 lastFrame = 0;
void setFPS(int fps) {
	Uint64 currentFrame = SDL_GetTicks64();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	if (1000 / fps > deltaTime) {
		SDL_Delay(1000 / fps - deltaTime);
	}
}

void initWindow(const int width, const int height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());

		exit(1);
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		printf("Couldn't create window: %s\n", SDL_GetError());

		exit(1);
	}

	glContext = SDL_GL_CreateContext(window);
	if (!glContext) {
		printf("Couldn't create OpenGL context: %s\n", SDL_GetError());
		exit(1);
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		exit(1);
	}

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}

void deleteWindow() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}