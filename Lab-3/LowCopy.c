#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char block[1024];
	int in, out;
	int nread;
	unsigned int i=0;

	// Exception Handling
	if(argc != 3) {
		printf("Usage: LowCopy [src-file] [dst-file]\n");
		exit(1);
	}

	// Open src/dst files using Low-level file handling functions
	in = open(argv[1], O_RDONLY);
	out = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

	// Copy from in to out, 1024bytes per loop
	while((nread = read(in, block, sizeof(block))) > 0) {
		write(out, block, nread);
		i++;
		// Print '.' every block
		if(i>sizeof(block)) {
			printf(".");
			fflush(stdout);	// Empty the output buffer
			i=0;
		}
	}

	// Print error when read fails
	if(nread == -1) {
		printf("Copy Error!\n");
		exit(1);
	}

	printf("\nCopy finished!\n");

	close(in);
	close(out);
	exit(0);
}
