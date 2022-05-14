#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void print_line(FILE *fp, int pos_in_line) {
	assert(fseek(fp, -pos_in_line, SEEK_CUR) == 0);

	for(char ch = fgetc(fp); ch != '\n'; ch = fgetc(fp)) {
		fputc(ch, stdout);
	}

	fputc('\n', stdout);
}

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}

	FILE *fp;

	if(argc < 3) {
		fp = stdin;
	} else {
		fp = fopen(argv[2], "r");
	}

	if(fp == NULL) {
		printf("wgrep: cannot open file\n");
		exit(1);
	}

	char *searchterm = argv[1];
	int pos_in_search = 0;
	int pos_in_line = 0;

	for(char ch = fgetc(fp); !feof(fp); ch = fgetc(fp)) {
		pos_in_line++;

		if(ch == searchterm[pos_in_search]) {
			pos_in_search++;

			if(searchterm[pos_in_search] == '\0') {
				print_line(fp, pos_in_line);
				ch = '\n';
			}

		} else {
			pos_in_search = 0;
		}

		if(ch == '\n') {
			pos_in_line = 0;
			pos_in_search = 0;
		}

	}
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
