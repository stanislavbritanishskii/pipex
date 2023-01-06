#!/bin/sh
rm output
touch output
gcc utils.c tests.c libft/libft.a
./a.out;