#include "common_test.h"

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