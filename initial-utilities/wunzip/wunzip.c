#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("wunzip: file1 [file2 ...]\n");
    exit(EXIT_FAILURE);
  }

  FILE *file;
  int char_occurrences;
  char character;

  for (int i=1; i < argc; i++) {
    char *file_name = argv[i];
    if ((file = fopen(file_name, "r")) == NULL) {
      perror("wunzip: cannot open file");
      exit(EXIT_FAILURE);
    }

    while (fread(&char_occurrences, 4, 1, file)) {
      fread(&character, 1, 1, file);
      for (int j = 0; j < char_occurrences; j++) {
        fwrite(&character, 1, 1, stdout);
      }
    }
    fclose(file);
  }
}
