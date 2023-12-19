nasm -felf64 -o lib.o lib.s &&
ar rcs lib.a lib.o &&
gcc -o ./test main.c lib.a
