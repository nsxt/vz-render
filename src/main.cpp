#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

void bind_console() {
	if (!AllocConsole()) 
		return;

	// redirect the CRT standard input, output, error handles to the console
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

	SetConsoleTitle("VZ-Render Debug Console");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}

void unbind_console() {
	FreeConsole();
}

void stream_test() {
	std::cout << "Console stream start..." << std::endl;
}

void glm_test() {
	glm::vec4 pos(10.f, 5.f, 1.f, 0.f);	
	int len = pos.length();

	std::cout << std::endl;
	std::cout << "pos : " << pos.x << "," << pos.y << "," << pos.z << "," << pos.w << std::endl;
	std::cout << "len : " << len << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int run_app() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(800, 600, "VZ Render", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();

	return 0;
}

int main(void) {	
	bind_console();

	stream_test();
	glm_test();

	int exit_code = run_app();

	unbind_console();

	return exit_code;
}