#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <Windows.h>

#include "game.h"

#define WIDTH 800
#define HEIGHT 600

// Variables

Game game(WIDTH, HEIGHT);
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Callback functions

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
	// Init

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "BreakoutGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return  -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, WIDTH, HEIGHT);

	// Create game object

	game.init();

	// Render loop

	while (!glfwWindowShouldClose(window)) {
		// -- 60 FPS --
		while (glfwGetTime() < lastFrame + 1.0 / 60) {
			Sleep(0.05);
		}

		// -- Delta time --
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// -- User input --
		game.processInput(deltaTime);

		// -- Physics --
		game.update(deltaTime);

		// -- Render --
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		game.render();

		// -- Events + Buffer --
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			game.setKey(key, true);
		else if(action == GLFW_RELEASE)
			game.setKey(key, false);
	}

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		GLint polyMode[2];
		glGetIntegerv(GL_POLYGON_MODE, &(*polyMode));

		if (polyMode[0] == GL_FILL) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}