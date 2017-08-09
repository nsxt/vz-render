//////////////////////////////////////////////////////
//----------------------------------------------------
/*

	something title....

*/
//----------------------------------------------------
//////////////////////////////////////////////////////
#include "core.h"


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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	VzCore::Timer.initialize();
	VzCore::Camera.initialize();

	return 0;
}

//////////////////////////////////////////////////////
//
int run_app() {
	if (init_app() < 0) 
		return -1;
	
	ImGui_ImplGlfwGL3_Init(VzGlobal::WindowCtx, true);
	
	init_dummy();

	while (!glfwWindowShouldClose(VzGlobal::WindowCtx)) {
		glfwPollEvents();

		VzCore::Timer.update();

				
		VzCore::DeltaTime += VzCore::Timer.time_difference();
		if (VzCore::DeltaTime >= 1.0f / 60.f) {
			VzCore::Timer.update_frame_count();
			process_input(VzGlobal::WindowCtx);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			render_dummy();

			ImGui_ImplGlfwGL3_NewFrame();
			ImGui::Begin("VZ-Render Property");
			ImGui::End();
			ImGui::Render();

			glfwSwapBuffers(VzGlobal::WindowCtx);

			VzCore::DeltaTime = 0.0f;

			//char tmp[128];
			//sprintf(tmp, "VZ-Render OpenGL @ fps: %.2f", VzCore::Timer.fps());
			//glfwSetWindowTitle(VzGlobal::WindowCtx, tmp);
		}

	}

	destroy_dummy();

	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();

	return 0;
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
		VzCore::Camera.process_keyboard(VzCamera::FORWARD, VzCore::DeltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		VzCore::Camera.process_keyboard(VzCamera::BACKWARD, VzCore::DeltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		VzCore::Camera.process_keyboard(VzCamera::LEFT, VzCore::DeltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		VzCore::Camera.process_keyboard(VzCamera::RIGHT, VzCore::DeltaTime);
}

//////////////////////////////////////////////////////
//
// Dummy model process
//

void init_dummy() {
	VzCore::Cube.create();
}
void render_dummy() {
	VzCore::Cube.render();
}
void destroy_dummy() {
	VzCore::Cube.destroy();
}