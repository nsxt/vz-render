//---------------------------------------------------
/*
	something title....
*/
//---------------------------------------------------
#include "core.h"

//////////////////////////////////////////////////////
//
int main(void) {
	bind_console();

	stream_test();
	glm_test();

	int exit_code = run_app();

	unbind_console();

	return exit_code;
}