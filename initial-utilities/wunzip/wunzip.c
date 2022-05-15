#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}


	for(int file_no = 1; file_no < argc; file_no++) {
		int ch;
		int num_consecutive = 0;
		FILE* fp = fopen(argv[file_no], "r");

		if(fp == NULL) {
			printf("wunzip: cannot open file\n");
		}

		while(!feof(fp)) {
			for(int i = 0; i < num_consecutive; i++) {
				fputc(ch, stdout);
			}

			fread(&num_consecutive, sizeof(int), 1, fp);
			ch = fgetc(fp);
		}

		fclose(fp);
	}

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
