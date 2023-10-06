clang main.c -o main
clang -framework Foundation -dynamiclib dylib.m libsubsidiary/*.c -o mod.dylib
