//////////////////////////////////////////////////////
//----------------------------------------------------
/*

	something title....

*/
//----------------------------------------------------
//////////////////////////////////////////////////////
#include "core.h"
#include <glm/gtc/type_ptr.hpp>

//////////////////////////////////////////////////////
//
int run_app() {
	if (init_app() < 0)
		return -1;

	while (!glfwWindowShouldClose(VzGlobal::WindowCtx)) {
		VzCore::Timer.think();
		glfwPollEvents();
		process_input(VzGlobal::WindowCtx);

		if (VzCore::Timer.one_frame()) {
			clear_buffer();
			
			render_ui();
			render_dummy();

			glfwSwapBuffers(VzGlobal::WindowCtx);
		}

		VzCore::Timer.post_think();
	}

	return deinit_app();
}

//////////////////////////////////////////////////////
//
int init_app() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	VzGlobal ::WindowCtx = glfwCreateWindow(1280, 720, "VZ Render", NULL, NULL);
	if (VzGlobal::WindowCtx == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(VzGlobal::WindowCtx);

	glfwSetFramebufferSizeCallback(VzGlobal::WindowCtx, framebuffer_size_callback);
	glfwSetCursorPosCallback(VzGlobal::WindowCtx, mouse_callback);
	glfwSetScrollCallback(VzGlobal::WindowCtx, scroll_callback);

	glfwSetWindowTitle(VzGlobal::WindowCtx, "VZ-Render alpha version");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	VzCore::Timer.initialize();
	VzCore::Timer.set_fps(60.0f);

	VzCore::Camera.initialize();
	
	VzCore::Font.initialize();
	
	print_vendor_info();

	ImGui_ImplGlfwGL3_Init(VzGlobal::WindowCtx, true);

	init_dummy();

	return 0;
}

int deinit_app() {
	VzCore::Font.deinitialize();
	destroy_dummy();
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();

	return 0;
}

void clear_buffer() {
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, glm::value_ptr(VzColor::DarkGray));
	glClearBufferfv(GL_DEPTH, 0, &one);
}

void render_ui() {
	VzCore::UI.think();
}

//////////////////////////////////////////////////////
// glfw : whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	static bool isFirstMove = true;
	static float lastX = (float)VzCore::Camera.ScreenWidth / 2.0f;
	static float lastY = (float)VzCore::Camera.ScreenHeight / 2.0f;

	if (isFirstMove) {
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);
		isFirstMove = false;
	}

	float xoffset = static_cast<float>(xpos - lastX);
	float yoffset = static_cast<float>(lastY - ypos);

	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	int mouseBtn = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (mouseBtn == GLFW_PRESS)
		VzCore::Camera.process_mouse_movement(xoffset, yoffset);
}

//////////////////////////////////////////////////////
// glfw : whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	VzCore::Camera.process_mouse_scroll(static_cast<float>(yoffset));
	ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);
}

//////////////////////////////////////////////////////
//
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//////////////////////////////////////////////////////
//
void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		VzCore::Camera.process_keyboard(VzCamera::FORWARD, VzCore::Timer.time_difference());

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		VzCore::Camera.process_keyboard(VzCamera::BACKWARD, VzCore::Timer.time_difference());

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		VzCore::Camera.process_keyboard(VzCamera::LEFT, VzCore::Timer.time_difference());

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		VzCore::Camera.process_keyboard(VzCamera::RIGHT, VzCore::Timer.time_difference());
}

//////////////////////////////////////////////////////
//
// Dummy model process
//

void init_dummy() {
	//VzCore::Cube.create();

	VzCore::SquareMatrixEntity.create();
	VzCore::VoxelBlockEntity.create();

	VzCore::PointMatrixEntity.create(VzCore::VoxelBlockEntity.get_block_density(), 16U);

}
void render_dummy() {
	//VzCore::Cube.render();	
	
	VzCore::SquareMatrixEntity.render();
	VzCore::PointMatrixEntity.render();

	VzCore::VoxelBlockEntity.render();
}
void destroy_dummy() {
	//VzCore::Cube.destroy();
	
	VzCore::SquareMatrixEntity.destroy();
	VzCore::PointMatrixEntity.destroy();

	VzCore::VoxelBlockEntity.destroy();
}