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

/*
 * Note that everything other than SubsidiaryHookFunction has been redacted from this source.
*/

#include <objc/runtime.h>
#include "libsubsidiary.h"
#include <mach-o/dyld.h>
#include "fishhook.h"
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <unistd.h>

#ifdef __LP64__
typedef struct mach_header_64 mach_header_t;
typedef struct segment_command_64 segment_command_t;
typedef struct section_64 section_t;
#else
typedef struct mach_header mach_header_t;
typedef struct segment_command segment_command_t;
typedef struct section section_t;
#endif

void SubsidiaryGenericHookMethod(Class cls, SEL name, IMP imp, IMP *orig) {
 Method hookMethod = class_getInstanceMethod(cls, name);
 if (!hookMethod) { return; }
 *orig = class_replaceMethod(cls, name, imp, method_getTypeEncoding(hookMethod));
}

subsid_err SubsidiaryGenericHookMethodWithError(Class cls, SEL name, IMP imp, IMP *orig) {
 if (!imp) {
  return Subsid_InvalidArgs;
 }
 Method hookMethod = class_getInstanceMethod(cls, name);
 if (!hookMethod) {
  return Subsid_NoSel;
 }
 *orig = class_replaceMethod(cls, name, imp, method_getTypeEncoding(meth));
 return Subsid_Succeed;
}

void SubsidiaryHookFunction(const char *functionName, void *hook, void **origFunc) {
 /* before we use fishhook, we must make the memory writeable */
 void *mainProgramHandle = dlopen(NULL, RTLD_NOW);
 if (!mainProgramHandle) {
  fprintf(stderr, "dlopen failed: %s\n", dlerror());
  return;
 }
 int64_t *origFuncPtr = dlsym(mainProgramHandle, functionName);
 if (!origFuncPtr) {
  fprintf(stderr, "dlsym %s failed\n", dlerror());
  return;
 }
 size_t pageSize = sysconf(_SC_PAGESIZE);
 uintptr_t start = (uintptr_t)origFuncPtr;
 uintptr_t end = start + 1;
 uintptr_t pageStart = start & -pageSize;
 mprotect((void *)pageStart, end - pageStart, PROT_READ | PROT_WRITE | PROT_EXEC);
 printf("made page writable\n");
 /* our memory is writeable now */
 /* TODO: Don't hardcode this, use getprogname() to help find FS */
 const char *processName = "/Users/0xilis/Library/Application Support/Steam/steamapps/common/Geometry Dash/Geometry Dash.app/Contents/MacOS/Geometry Dash";
 uint32_t dyld_image_count = _dyld_image_count();
 //find our image
 for (int i=0; i<dyld_image_count; i++) {
  const char *name = _dyld_get_image_name(i); //get image name
  if (strcmp(name, processName) == 0) { //check if we found our image
    const mach_header_t *header = (const mach_header_t *)_dyld_get_image_header(i);
    rebind_symbols_image(header, _dyld_get_image_vmaddr_slide(i), (struct rebinding[1]){{functionName, hook, origFunc }}, 1);
    return;
  }
 }
 printf("failed to hook symbol: %s\n",functionName);
}

void copyright(void) {
 printf("Subsidiary is by Snoolie K / 0xilis.\n");
 printf("fishhook by facebook. (Copyright (c) 2013, Facebook, Inc. All rights reserved.)\n");
}
