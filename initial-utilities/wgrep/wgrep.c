#include <stdio.h>
#include <string.h>

int grep(char *pattern, FILE *file) {
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern)) {
            printf("%s", line);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    FILE *file;
    if (argc == 2) {
        file = stdin;  // read from standard input
    } else {
        file = fopen(argv[2], "r");
        if (file == NULL) {
            printf("wgrep: cannot open file\n");
            return 1;
        }
    }

    int x = grep(argv[1], file);
    if (file != stdin) {
        fclose(file);
    }
    return x;
}
