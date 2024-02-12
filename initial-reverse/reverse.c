#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // for hardlinked files

#define MAX_LINE_LENGTH 1024

void reverse(FILE *input, FILE *output) {
    char **lines = NULL; // array of strings
    size_t count = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), input)) {
        lines = realloc(lines, (count + 1) * sizeof(*lines));
        if (!lines) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        lines[count++] = strdup(line);
    }

    while (count--) {
        fprintf(output, "%s", lines[count]);
        free(lines[count]); // freeing memory
    }

    free(lines);
}

int main(int argc, char *argv[]) {
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n"); // wrong usage
        return 1;
    }

    FILE *input = argc > 1 ? fopen(argv[1], "r") : stdin;
    if (!input) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
        return 1;
    }

    FILE *output = argc > 2 ? fopen(argv[2], "w") : stdout;
    if (!output) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
        return 1;
    }

    // if (argc > 2 && strcmp(argv[1], argv[2]) == 0) {
    // fprintf(stderr, "reverse: input and output file must differ\n"); not working for hardlinked files obviously
    // return 1;
    // }

    struct stat stat1, stat2;

    if (argc > 2) {
         if (stat(argv[1], &stat1) == -1 || stat(argv[2], &stat2) == -1) {
            fprintf(stderr, "reverse: error with stat\n");
            return 1;
    }

    if (stat1.st_ino == stat2.st_ino) { // compare inode(index node; stores attributes and disk block locations of the object's data) number of two files
        fprintf(stderr, "reverse: input and output file must differ\n");
        return 1;
    }
    }


    reverse(input, output);

    if (input != stdin) fclose(input);
    if (output != stdout) fclose(output);

    return 0;
}
