#include <stdio.h>
#include <objc/runtime.h>

void SubsidiaryGenericHookMethod(Class cls, SEL name, IMP imp, IMP *orig);
void SubsidiaryHookFunction(const char *functionName, void *hook, void **origFunc);