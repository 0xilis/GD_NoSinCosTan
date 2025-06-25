#include <stdio.h>
#include <spawn.h>
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */
#define GD_PATH "/Users/0xilis/Library/Application Support/Steam/steamapps/common/Geometry Dash/Geometry Dash.app/Contents/MacOS/Geometry Dash"
#define DYLIB_PATH "/Users/0xilis/Downloads/0/GitGub/GD Modloader/mod.dylib"
#include "resource_management.h"

#include "libsubsidiary/libsubsidiary.h"

static FILE *(*orig_fopen)(const char *path, const char *mode);

FILE *hook_fopen(const char *path, const char *mode) {
 //printf("fopen path: %s\n",path);
 //printf("fopen mode: %s\n",mode);
 resourcesPath = "/Users/0xilis/Downloads/0/GitGub/GD Modloader/texture-pack/";
 char *fileName = get_file_name_from_path(path);
 char *ourFilePath = find_resource(fileName);
 free(fileName);
 FILE *fp = orig_fopen(ourFilePath, mode);
 free(ourFilePath);
 if (fp) {
  printf("using texture pack for: %s\n",ourFilePath);
  return fp;
 }
 printf("could not find pack for: %s\n",path);
 return orig_fopen(path, mode);
}

__attribute__((constructor)) static void init() {
 printf("hello from dylib.c!\n");
 SubsidiaryHookFunction("fopen", hook_fopen, (void *)&orig_fopen);
}