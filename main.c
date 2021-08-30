#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*archive;

	fd = open("/Users/dlerma-c/Desktop/42/GNL/fichero1", O_RDONLY);
	if (fd == -1)
	{
		printf("(%d)Error al abrir el archivo.\n", fd);
		return (0);
	}
	archive = get_next_line(fd);
	printf("\n\tArchivo: \n%s\n", archive);
	system("\nleaks a.out");
	return (0);
}
