#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char *get_next_line(int fd)
{
	ssize_t	size;
	char	*buf;

	buf = calloc(BUFFER_SIZE, sizeof(char));
	size = read(fd, buf, BUFFER_SIZE);
	if (size == 0)
	{
		printf("Archivo vacío\n");
		return (NULL);
	}
	printf("SIZE: %d\n",(int)size);
	return (buf);
}

int main(void)
{
	int		fd;
	char	*archive;

	fd = open("/mnt/c/Users/danie/Desktop/C/prueba/getLine/fichero1", O_RDONLY);
	if (fd == -1)
	{
		printf("(%d)Error al abrir el archivo.\n", fd);
		return (0);
	}
	archive = get_next_line(fd);
	printf("Archivo: %s\n", archive);
	return (0);
}

