clang main.c -o main
clang -framework Foundation -dynamiclib dylib.c resource_management.c libsubsidiary/*.c -o mod.dylib
