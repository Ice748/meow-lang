#include "modules/console.h"

void println(char *arg) {
  printf("%s\n", arg);
}

void print(char *arg) {
  printf("%s", arg);
}

int console_module(char *str) {
  char *println_arg = getArgString(str);
  if (println_arg != NULL) {
    println(println_arg);
    free(println_arg);
    return 1;
  }

  char *print_arg = getArgString(str);
  if (print_arg != NULL) {
    print(print_arg);
    free(print_arg);
    return 1;
  }

  return 0;
}
