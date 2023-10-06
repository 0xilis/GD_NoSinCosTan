clang main.c -o main
clang -framework Foundation -dynamiclib dylib.c libsubsidiary/*.c -o mod.dylib
