#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Usage: %s [file]\n", argv[0]);
		exit(1);
	}

	FILE* fp = fopen(argv[1], "r");

	if(fp == NULL) {
		printf("Could: cannot open file\n");
	}

	int num_repeats = 1;
	char previous_char = '\0';
	for(char ch = fgetc(fp); !feof(fp); ch = fgetc(fp)) {
		if(ch == previous_char) {
			num_repeats++;
		} else {
			fwrite(&num_repeats, 1, 4, stdout);
			fputc(previous_char, stdout);
			previous_char = ch;
			num_repeats = 1;
		}
		
	}

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
