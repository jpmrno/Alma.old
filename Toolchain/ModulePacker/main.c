#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE !FALSE

#define BUFFER_SIZE 128

#define OUTPUT_FILE "system.bin"

typedef struct {
	char **array;
	int length;
} array_t;

int buildImage(array_t fileArray);

void write_size(FILE * target, char * filename);
int write_file(FILE * target, FILE * source);

int checkFiles(array_t fileArray);

int main(int argc, char *argv[]) {
	printf("x64BareBones Module Packer (C) v0.1.1\n");

	if(argc < 2) {
		printf("Usage: \n");
		printf("\t$> mp.bin <kernel_binary> <user_binary_0> ... <user_binary_N>");

		return 1;
	}

	array_t fileArray = {&argv[1], argc -1};

	if(!checkFiles(fileArray)) {
		return 1;
	}

	return !buildImage(fileArray);
}

int buildImage(array_t fileArray) {
	int i, extraBinaries;
	FILE * target, * source;

	if((target = fopen(OUTPUT_FILE, "w")) == NULL) {
		printf("Can't create target file\n");

		return FALSE;
	}

	// First, write the kernel
	source = fopen(fileArray.array[0], "r");
	write_file(target, source);

	// Write how many extra binaries we got.
	extraBinaries = fileArray.length - 1;
	fwrite(&extraBinaries, sizeof(extraBinaries), 1, target);
	fclose(source);

	for (i = 1 ; i < fileArray.length ; i++) {
		source = fopen(fileArray.array[i], "r");

		// Write the file size;
		write_size(target, fileArray.array[i]);
		// Write the binary
		write_file(target, source);

		fclose(source);
	}

	fclose(target);

	return TRUE;
}


int checkFiles(array_t fileArray) {
	int i;

	for(i = 0; i < fileArray.length ; i++) {
		if(access(fileArray.array[i], R_OK)) {
			printf("Can't open file: %s\n", fileArray.array[i]);
			return FALSE;
		}
	}

	return TRUE;
}

void write_size(FILE * target, char * filename) {
	struct stat st;
	uint32_t size;

	stat(filename, &st);
	size = st.st_size;
	fwrite(&size, sizeof(uint32_t), 1, target);
}


int write_file(FILE * target, FILE * source) {
	char buffer[BUFFER_SIZE];
	int read;

	while (!feof(source)) {
		read = fread(buffer, 1, BUFFER_SIZE, source);
		fwrite(buffer, 1, read, target);
	}

	return TRUE;
}
