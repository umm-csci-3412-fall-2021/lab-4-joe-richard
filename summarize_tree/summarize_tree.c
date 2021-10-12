#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static int num_dirs, num_regular;

//checks whether the given path is a directory
bool is_dir(const char* path) {
	struct stat buf;
	int stat_error = stat(path, &buf);

	if(stat_error == 0) {
		return S_ISDIR(buf.st_mode);
	}
	fprintf(stderr, "We were unable to stat the path provided.\n");
	fprintf(stderr, "Path Name: %s\n", path);
	exit(1);
}

void process_path(const char*);

void process_directory(const char* path) {
	num_dirs++;

	int chdir_error = chdir(path);
	if(chdir_error != 0) {
		perror("Cannot chdir into the path\n");
		fprintf(stderr, "Path name: %s\n", path);
		exit(1);
	}

	DIR *dir = opendir(".");
	struct dirent *child;
	//look at every file in the directory and recursively call process_path
	while((child = readdir(dir)) != NULL) {
		if(strcmp(child->d_name, "..") == 0 || strcmp(child->d_name, ".") == 0) {
			continue;
		}
		process_path(child->d_name);
	}
	closedir(dir);

	int end_chdir_error = chdir("..");
	if(end_chdir_error != 0) {
		fprintf(stderr, "Cannot go back into the previous directory from %s\n", path);
		exit(1);
	}
}

void process_file(const char* path) {
	num_regular++;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
