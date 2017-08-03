#include "common_test.h"
#include "plane.h"

GLFWwindow* window = nullptr;
VzPlane plane(glm::vec3(0.f, 0.f, 0.f));

int init_app();

void init_dummy() {	
	plane.create();
}

void render_dummy() {
	plane.render();
}


void destroy_dummy() {
	plane.destroy();
}

int run_app() {
	if (init_app() < 0) return -1;
	
	ImGui_ImplGlfwGL3_Init(window, true);
	
	init_dummy();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();
		process_input(window);

		ImGui::Begin("Test Window");
		ImGui::End();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render_dummy();

		ImGui::Render();
		glfwSwapBuffers(window);
	}

	destroy_dummy();

	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int init_app() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(1280, 720, "VZ Render", NULL, NULL);
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

	return 0;
}
