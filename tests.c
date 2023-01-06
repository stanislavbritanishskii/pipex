#include "pipex.h"
int main()
{
	int fd = open("test_OUTPUT.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
	read_from_to("end", STDIN_FILENO, fd);
	close(fd);
}