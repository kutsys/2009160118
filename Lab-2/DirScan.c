#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir, int depth) {
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return;
	}

	chdir(dir);
	
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) continue;
			
			// 받아들인 디렉토리 명이 . 으로 시작한다면 while문 스킵
			if(entry->d_name[0] == '.') continue;			

			printf("%*s%s/\n",depth,"",entry->d_name);
			printdir(entry->d_name,depth+4);
		} else {
			// 받아들인 파일명이 . 으로 시작한다면 while문 스킵
			if(entry->d_name[0] == '.') continue;			
			printf("%*s%s\n",depth,"",entry->d_name);
		}
	}
	chdir("..");
	closedir(dp);
}

int main() {
	printf("Directory scan of Current Directory:\n");
	printdir(".",0);
	printf("done.\n");
	exit(0);
}

