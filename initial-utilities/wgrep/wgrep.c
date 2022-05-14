#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Dynamic list
void append(char** buffer, char ch, int curr_pos, int* len) {
	if(*buffer == NULL) {
		*len = 16; // Initial buffer size
		*buffer = malloc(*len);
	}

	if(curr_pos + 1 >= *len) {
		*len *= 2; // Buffer doubles each time
		*buffer = realloc(*buffer, *len);
	}

	(*buffer)[curr_pos] = ch;
	(*buffer)[curr_pos + 1] = '\0';
}

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}

	char* searchterm = argv[1];
	int arg_num = 2; // Initialize to 2nd argument
	FILE *fp;
	do {
		if(argc < 3) {
			fp = stdin;
		} else {
			fp = fopen(argv[arg_num++], "r");
		}

		if(fp == NULL) {
			printf("wgrep: cannot open file\n");
			exit(1);
		}

		char* line = NULL;
		int len = 0;
		int pos_in_search = 0;
		int pos_in_line = 0;
		bool is_found = false;

		for(char ch = fgetc(fp); !feof(fp); ch = fgetc(fp)) {
			append(&line, ch, pos_in_line, &len);

			pos_in_line++;

			if(ch == searchterm[pos_in_search]) {
				pos_in_search++;

				if(searchterm[pos_in_search] == '\0') {
					is_found = true;
					pos_in_search = 0;
				}

			} else {
				pos_in_search = 0;
			}


			if(ch == '\n') {
				if(is_found){
					printf("%s", line);
					is_found = false;
				}

				free(line);
				line = NULL;
				pos_in_line = 0;
				pos_in_search = 0;
				len = 0;
			}
		}
		fclose(fp);
	} while(arg_num < argc); 

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
