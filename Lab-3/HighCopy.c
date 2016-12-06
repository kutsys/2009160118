#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char block[1024];
	FILE *fin, *fout;
	int nread;
	unsigned int i=0;

	// Exception Handling
	if(argc != 3) {
		printf("Usage: HighCopy [src-file] [dst-file]\n");
		exit(1);
	}

	// Oepn src/dst files using High-level file handling functions
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	// Copy from fin to fout, 1024bytes per loop
	while((nread = fread(block, 1, sizeof(block), fin)) > 0) {
		fwrite(block, 1, nread, fout);
		i++;
		// Print '*' every block
		if(i>sizeof(block)) {
			printf("*");
			fflush(stdout);	// Empty the output buffer
			i=0;
		}
	}

	// Print error when read fails
	if(fin == NULL || fout == NULL) {
		printf("Copy Error!");
		exit(1);
	}

	printf("\nCopy finished!\n");

	fclose(fin);
	fclose(fout);
	exit(0);
}
