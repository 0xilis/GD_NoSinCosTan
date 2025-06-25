#include <stdio.h>
#include <spawn.h>
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */
#define GD_PATH "/Users/0xilis/Library/Application Support/Steam/steamapps/common/Geometry Dash/Geometry Dash.app/Contents/MacOS/Geometry Dash"
#define DYLIB_PATH "/Users/0xilis/Downloads/0/GitGub/GD Modloader/Source/GD_NoSinCosTan/mod.dylib"

void launchGD(void) {
 pid_t pid;
 const char* args[] = {"Geometry Dash", NULL};
 char* dylibPath = "DYLD_INSERT_LIBRARIES=/Users/0xilis/Downloads/0/GitGub/GD Modloader/Source/GD_NoSinCosTan/mod.dylib:/Users/0xilis/Library/Application Support/Steam/Steam.AppBundle/Steam/Contents/MacOS/steamclient.dylib:/Users/0xilis/Library/Application Support/Steam/steamapps/common/Geometry Dash/Geometry Dash.app/Contents/MacOS/libsteam_api.dylib:/Users/0xilis/Library/Application Support/Steam/Steam.AppBundle/Steam/Contents/MacOS/steamloader.dylib:/Users/0xilis/Library/Application Support/Steam/Steam.AppBundle/Steam/Contents/MacOS/steamservice.dylib";
 char **ugh = malloc(sizeof(char *) * strlen(dylibPath) + 1);
 char *const *envp = ugh;
 /* copy dylibPath to envp */
 *ugh = dylibPath;
 printf("envp: %s\n",*envp);
 posix_spawn(&pid, GD_PATH, NULL, NULL, (char* const*)args, envp);
}

int main(void) {
 launchGD();
 return 0;
}