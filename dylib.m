#include <stdio.h>
#include <spawn.h>
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */
#define GD_PATH "/Users/0xilis/Library/Application Support/Steam/steamapps/common/Geometry Dash/Geometry Dash.app/Contents/MacOS/Geometry Dash"
#define DYLIB_PATH "/Users/0xilis/Downloads/0/GitGub/GD Modloader/mod.dylib"

#include "libsubsidiary/libsubsidiary.h"

#include <objc/runtime.h>

static double (*orig_cos)(double x);

double hook_cos(double x) {
 //printf("cos called\n");
 return 0;
}

static double (*orig_sin)(double x);

double hook_sin(double x) {
 //printf("sin called\n");
 return 0;
}

static double (*orig_tan)(double x);

double hook_tan(double x) {
 //printf("tan called\n");
 return 0;
}

static double (*orig_acos)(double x);

double hook_acos(double x) {
 //printf("acos called\n");
 return 0;
}

static double (*orig_asin)(double x);

double hook_asin(double x) {
 //printf("asin called\n");
 return 0;
}

static double (*orig_atan)(double x);

double hook_atan(double x) {
 //printf("atan called\n");
 return 0;
}

static double (*orig_atan2)(double x);

double hook_atan2(double x) {
 //printf("atan2 called\n");
 return 0;
}

static double (*orig_acosh)(double x);

double hook_acosh(double x) {
 //printf("acosh called\n");
 return 0;
}

static double (*orig_asinh)(double x);

double hook_asinh(double x) {
 //printf("asinh called\n");
 return 0;
}

__attribute__((constructor)) static void init() {
 printf("hello from dylib.c!\n");
 SubsidiaryHookFunction("cos", hook_cos, (void *)&orig_cos);
 SubsidiaryHookFunction("sin", hook_sin, (void *)&orig_sin);
 SubsidiaryHookFunction("tan", hook_tan, (void *)&orig_tan);
 SubsidiaryHookFunction("acos", hook_acos, (void *)&orig_acos);
 SubsidiaryHookFunction("asin", hook_asin, (void *)&orig_asin);
 SubsidiaryHookFunction("atan", hook_atan, (void *)&orig_atan);
 SubsidiaryHookFunction("atan2", hook_atan2, (void *)&orig_atan2);
 SubsidiaryHookFunction("acosh", hook_acosh, (void *)&orig_acosh);
 SubsidiaryHookFunction("asinh", hook_asinh, (void *)&orig_asinh);
 SubsidiaryHookFunction("asinh", hook_asinh, (void *)&orig_asinh);
}