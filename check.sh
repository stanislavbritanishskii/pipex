#!/bin/sh
rm output
touch output
make
echo './pipex fffile.c "ls -la" wc output'
./pipex fffile.c ~/b.sh cat output
< fffile.c ls -la | wc > output2
diff output output2