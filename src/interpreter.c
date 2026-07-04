#include "interpreter.h"
#include "modules/console.h"

char *getArgString(char *ptr, const char *module, const char *function);

int run(FILE *file) {
  if (file == NULL) {
    printf("%s\n", ERROR_005); // ERROR 005: Cannot open file.
    return 1;
  }

  int modules[1]; // 0: console
  for (size_t idx = 0; idx < sizeof(modules); idx++) {
    modules[idx] = 0;
  }

  char buffer[256];
  int line = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    buffer[strcspn(buffer, "\n")] = '\0';
    line++;

    char *import_args = getArgString(buffer, NULL, "@import");
    char *deimport_args = getArgString(buffer, NULL, "@deimport");
    if (import_args != NULL || deimport_args != NULL) {
      if (strcmp(import_args, "console") modules[0] = import_args ? 1 : 0;
      else {
        printf("Error in line %d:\n%s\n", line, ERROR_006); // ERROR 006: Unknown module.
        return 1;
      }

      free(import_args ? import_args : deimport_args);
      continue;
    }

    char *launch_args = getArgString(buffer, NULL, "@launch");
    if (launch_args != NULL) {
      FILE *launch_file = fopen(launch_args, "r");
      run(launch_file);
    }

    if (modules[0]) {
      console_module();
    }

    printf("Error in line %d\n", line);
    return 1;
  }

  fclose(file);
  return 0;
}

char *getArgString(char *ptr, const char *module, const char *function) {
  if (ptr == NULL || function == NULL) {
    return NULL;
  }
  
  while (isspace((unsigned char)*ptr)) ptr++;
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
