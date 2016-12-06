#include <stdio.h>
#include <stdlib.h>

int main() {
	// getenv()
	printf("getenv():\n");
	printf("$HOME: %s\n", getenv("HOME"));
	printf("$PS1: %s\n", getenv("PS1"));
	printf("$PATH: %s\n", getenv("PATH"));
	printf("$LD_LIBRARY_PATH: %s\n", getenv("LD_LIBRARY_PATH"));

	// setenv()
	printf("\nsetenv():\n");
	printf("$TEST_ENV %s\n", getenv("TEST_ENV"));
	setenv("TEST_ENV", "1234", 1);
	printf("$TEST_ENV %s\n", getenv("TEST_ENV"));

	exit(0);
}
