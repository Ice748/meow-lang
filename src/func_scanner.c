#include "interpreter.h"

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
