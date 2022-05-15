#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

int main(int argc, char* argv[]) {
#ifdef TIME
	FILE* out = fopen("test.zip", "w");
	clock_t begin = clock();
#else
	FILE* out = stdout;
#endif
	if(argc < 2) {
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}

	int num_repeats = 0;
	char previous_char;
	int ch;

	for(int i = 1; i < argc; i++) {
		FILE* fp = fopen(argv[i], "r");

		if(fp == NULL) {
			printf("wzip: cannot open file\n");
			exit(1);
		}

		if(i == 1) {
			previous_char = fgetc(fp);
		}

		while((ch = fgetc(fp)) != EOF) {
			num_repeats++;
			if(ch != previous_char) {
				fwrite(&num_repeats, sizeof(int), 1, out);
				fputc(previous_char, out);
				num_repeats = 0;
				previous_char = ch;
			} 
		}
		fclose(fp);
	}

	num_repeats++;
	fwrite(&num_repeats, sizeof(int), 1, out);
	fputc(previous_char, out);
#ifdef TIME
	clock_t end = clock();
	printf("Time: %lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
	fclose(out);
#endif

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
