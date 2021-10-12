#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#define BUF_SIZE 1024

bool is_vowel(char c) {
	char lowercase = tolower(c);
	if(lowercase == 'a' || lowercase == 'e' || lowercase == 'i'
			|| lowercase == 'o' || lowercase == 'u') {
		return true;
	}
	return false;
}

/*
 * Copy all the non-vowels from in_buf to out_buf.
 * num_chars indicates how many characters are in in_buf,
 * and this function should return the number of non-vowels that
 * that were copied over.
 *
 * As a precondition, out_buf should be at least as large as num_chars.
 */
int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
	int chars_copied = 0;
	for (int i = 0; i < num_chars; i++) {
		if (!is_vowel(in_buf[i])) {
			out_buf[chars_copied] = in_buf[i];
			chars_copied++;
		}
	}
	return chars_copied;
}

/*
 * Copy all the non-vowels from inputFile to outputFile.
 * Create input and output buffers, and use fread() to repeatedly read
 * in a buffer of data, copy the non-vowels to the output buffer, and
 * use fwrite to write that out.
 */
void disemvowel(FILE* inputFile, FILE* outputFile) {
	char in_buf[BUF_SIZE];
	char out_buf[BUF_SIZE];
	while(!feof(inputFile)) {
		int num_chars_read = fread(in_buf, sizeof(char), BUF_SIZE, inputFile);
		int non_vowel_count = copy_non_vowels(num_chars_read, in_buf, out_buf);
		fwrite(out_buf, sizeof(char), non_vowel_count, outputFile);
	}
}

int main(int argc, char *argv[]) {
	// This sets these to `stdin` and `stdout` by default.
	// You then need to set them to user specified files when the user
	// provides files names as command line arguments.
	FILE *inputFile = stdin;
	FILE *outputFile = stdout;
	if(argc == 2) {
		inputFile = fopen(argv[1], "r");
	} else if(argc == 3){
		inputFile = fopen(argv[1], "r");
		outputFile = fopen(argv[2], "w");
	} else if(argc > 3) {
		fprintf(stderr, "Usage: %s [input_file] [output_file]\n", argv[0]);
		exit(1);
	}

	if(inputFile == NULL) {
		fprintf(stderr, "Can't open input file for reading\n");
		exit(1);
	}
	if(outputFile == NULL) {
		fprintf(stderr, "Can't open output file for writing\n");
		exit(1);
	}

    	disemvowel(inputFile, outputFile);

	if(inputFile != stdin) {
		fclose(inputFile);
	}
	if(outputFile != stdout) {
		fclose(outputFile);
	}
	return 0;
}

