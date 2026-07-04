#include <stdio.h>
#include <string.h>
#include "meow-lang.h"
#include "interpreter.h"

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    printf("%s\n", ERROR_001); // ERROR 001: Too few arguments.
    return 1;
  }

  if (strcmp(argv[1], "run") == 0) {
    if (argc < 3) {
      printf("%s\n", ERROR_001); // ERROR 001: Too few arguments.
      return 1;
    } else if (argc > 3) {
      printf("%s\n", ERROR_002); // ERROR 002: Too much arguments.
      return 1;
    }

    FILE *file = fopen(argv[2], "r");
    return run(file);
  }

  if (strcmp(argv[1], "version") == 0) {
    if (argc > 2) {
      printf("%s\n", ERROR_002); // ERROR 002: Too much arguments.
      return 1;
    }

    printf("%s\n", VERSION);
    return 0;
  }

  printf("%s\n", ERROR_003); // ERROR 003: Unknown command.
  return 1;
}
