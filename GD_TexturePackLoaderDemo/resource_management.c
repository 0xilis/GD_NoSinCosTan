/*
 * Copyright (C) 2023 Snoolie K / 0xilis. All rights reserved.
 *
 * This document is the property of Snoolie K / 0xilis.
 * It is considered confidential and proprietary.
 *
 * This document may not be reproduced or transmitted in any form,
 * in whole or in part, without the express written permission of
 * Snoolie K / 0xilis.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource_management.h"

/* Resource Finder */

char *find_resource_path(char* runPath) {
  int runPathLen = strlen(runPath);
  /* This may be i > 0 instead idk */
  for (int i = runPathLen; i >= 0; i--) {
    if (runPath[i] == '/') {
      /* Copy into resourcesPath */
      /* Cut the beginning and ending " */
      char *start = &runPath[0];
      char *end = &runPath[i+1];
      /* Note the + 1 here, to have a null terminated substring */
      char *resourcesPath = (char *)calloc(1, end - start + 1);
      memcpy(resourcesPath, start, end - start);
      return resourcesPath;
    }
  }
  fprintf(stderr, "GravityGame Error: Unable to find resource path\n");
  exit(1);
}

char *find_resource(char* resource) {
  int resPathLen = strlen(resourcesPath);
  int resLen = strlen(resource);
  char *newResourcesPath = malloc(sizeof(char) * (resLen + resPathLen + 1));
  /* Copy resourcesPath to newResourcesPath */
  for (int i = 0; i < resPathLen; i++) {
    newResourcesPath[i] = resourcesPath[i];
    newResourcesPath[i+1] = '\0';
  }
  /* Copy resource to newResourcesPath */
  for (int i = 0; i < resLen; i++) {
    newResourcesPath[i+resPathLen] = resource[i];
    newResourcesPath[i+resPathLen+1] = '\0';
  }
  return newResourcesPath;
}

char *get_file_name_from_path(const char *path) {
 int pathLen = strlen(path);
 for (int i = pathLen; i >= 0; i--) {
  if (path[i] == '/') {
      const char *start = &path[i+1];
      const char *end = &path[pathLen];
      /* Note the + 1 here, to have a null terminated substring */
      char *resourcesPath = (char *)calloc(1, end - start + 1);
      memcpy(resourcesPath, start, end - start);
      return resourcesPath;
  }
 }
 /* could not find / in path; assume path is filename */
 return (char *)path;
}