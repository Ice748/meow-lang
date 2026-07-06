#include "interpreter.h"

char *getArgString(char *ptr, const char *module, const char *function);

int run(const char *file_name) {
  FILE *file = fopen(file_name, "r");

  if (file == NULL) {
    printf("%s\n", ERROR_005); // ERROR 005: Cannot open file.
    return 1;
  }

  int modules[1]; // 0: console
  for (size_t idx = 0; idx < sizeof(modules) / sizeof(modules[0]); idx++) {
    modules[idx] = 0;
  }

  char buffer[256];
  int line = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    buffer[strcspn(buffer, "\n")] = '\0';
    line++;

    char *ptr = buffer;

    while (isspace((unsigned char)*ptr)) ptr++;
    if (strlen(ptr) == 0) {
      continue;
    }

    char *import_arg = getArgString(ptr, NULL, "@import");
    if (import_arg != NULL) {
      if (strcmp(import_arg, "console") == 0) modules[0] = 1;
      else {
        printf("Error in %s in line %d:\n%s\n", file_name, line, ERROR_006); // ERROR 006: Unknown module.
        free(import_arg);
        fclose(file);
        return 1;
      }

      free(import_arg);
      continue;
    }

    char *deimport_arg = getArgString(ptr, NULL, "@deimport");
    if (deimport_arg != NULL) {
      if (strcmp(deimport_arg, "console") == 0) modules[0] = 0;
      else {
        printf("Error in %s in line %d:\n%s\n", file_name, line, ERROR_006); // ERROR 006: Unknown module.
        free(deimport_arg);
        fclose(file);
        return 1;
      }

      free(deimport_arg);
      continue;
    }

    char *launch_arg = getArgString(ptr, NULL, "@launch");
    if (launch_arg != NULL) {
      if (run(launch_arg) == 0) {
        free(launch_arg);
        continue;
      } else {
        free(launch_arg);
        fclose(file);
        return 1;
      }
      continue;
    }

    if (modules[0]) {
      if (console_module(ptr) == 1) continue;
    }

    printf("Error in %s in line %d\n", file_name, line);
    fclose(file);
    return 1;
  }

  fclose(file);
  return 0;
}

char *getArgString(char *ptr, const char *module, const char *function) {
  if (ptr == NULL || function == NULL) {
    return NULL;
  }

  if (module != NULL) {
    size_t module_len = strlen(module);
    if (strncmp(ptr, module, module_len) != 0) {
      return NULL;
    }
    ptr += module_len;

    while (isspace((unsigned char)*ptr)) ptr++;
    if (*ptr != '.') {
      return NULL;
    }
    ptr++;

    while (isspace((unsigned char)*ptr)) ptr++;
  }

  size_t function_len = strlen(function);
  if (strncmp(ptr, function, function_len) != 0) {
    return NULL;
  }
  ptr += function_len;

  while (isspace((unsigned char)*ptr)) ptr++;
  if (*ptr != '(') {
    return NULL;
  }
  ptr++;

  while (isspace((unsigned char)*ptr)) ptr++;
  if (*ptr != '"') {
    return NULL;
  }
  ptr++;

  char *result = NULL;
  size_t len = 0;

  while (*ptr != '"' && *ptr != '\0') {
    char *temp = realloc(result, len + 2);
    if (temp == NULL) {
      if (result != NULL) free(result);
      return NULL;
    }
    result = temp;

    result[len] = *ptr;
    len++;
    ptr++;
  }

  if (*ptr != '"') {
    free(result);
    return NULL;
  }
  ptr++;

  if (result != NULL) {
    result[len] = '\0';
  } else {
    result = calloc(1, 1);
    if (result == NULL) return NULL;
  }

  while (isspace((unsigned char)*ptr)) ptr++;
  if (*ptr != ')') {
    free(result);
    return NULL;
  }
  ptr++;

  return result;
}
