/**
* MIT License
* Copyright (c) 2025 broskobandi
* See LICENSE file for full details.
*/

/**
 * convert-to-string
 * Converts the content of input file(s) into a single c string.
 */

#include <stdio.h>
#include <string.h>
#include <c-string.h>

static const char help_message[] =
"\n"
"\tConverts content of input file(s) into a single c string.\n"
"\tOptionally, it saves the output file as C header file.\n"
"\n"
"Usage:\n"
"\n"
"\tconvert-to-c-string [input_file_1] [input_file_2] [...] [output_file] [options]\n"
"\n"
"Options:\n"
"\n"
"\t--help\t\tPrint this message\n"
"\t--header\tSave output as C header file\n"
"\n";

void print_help_and_exit() {
	printf("%s\n", help_message);
	exit(1);
}

int main(int argc, char *argv[]) {

	// Assumed default values
	int is_header = 0;
	int output_arg = argc - 1;
	int num_input_files = argc - 2;

	// Update values based on arguments and options passed
	if (argc < 3) {
		print_help_and_exit();
	}
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "--help") == 0) {
			print_help_and_exit();
		}
		if (strcmp(argv[i], "--header") == 0) {
			is_header = 1;
			num_input_files--;
			if (i == argc - 1) {
				output_arg--;
			}
		}
	}

	// Prepare string object
	STR_AUTO_T *str = STR_NEW;

	// Create and format header guard if --header option was passed
	if (is_header) {
		STR_AUTO_T *header_guard = STR_NEW_FROM(argv[output_arg]);
		STR_REPLACE(header_guard, "-", "_");
		STR_REPLACE(header_guard, ".h", "");
		STR_REPLACE(header_guard, ".", "_");
		STR_CAT(str, "#ifndef ");
		STR_CAT(str, STR_DATA(header_guard));
		STR_CAT(str, "_H\n");
		STR_CAT(str, "#define ");
		STR_CAT(str, STR_DATA(header_guard));
		STR_CAT(str, "_H\n");
	}
	STR_CAT(str, "const char str[] =\"");

	// Get data to be saved in the string variable
	// in the output file
	for (int i = 1; i < num_input_files + 1; i++) {
		FILE *file = fopen(argv[i], "r");
		if (!file) return 1;
		char c;
		while ((c = fgetc(file)) != EOF) {
			if (c == '\n') {
				STR_CAT(str, "\\n\"\"");
			} else if (c == '\t') {
				STR_CAT(str, "\\t");
			} else if (c == '\"') {
				STR_CAT(str, "\\\"");
			} else {
				STR_PUSH(str, c);
			}
		}
		fclose(file);
	}

	// Ensure the string is correctly terminated.
	if (
		STR_GET(str, STR_LEN(str) - 1) == '\"' &&
		STR_GET(str, STR_LEN(str) - 2) == '\"'
	) {
		STR_POP(str);
	}
	STR_PUSH(str, ';');

	// Close the header guard if --header option was passed
	if (is_header) {
		STR_CAT(str, "\n#endif");
	}

	// Create output file
	FILE *output = fopen(argv[output_arg], "w");
	if (!output) return 1;

	if (fputs(STR_DATA(str), output) != 1) return 1;

	fclose(output);

	return 0;
}
