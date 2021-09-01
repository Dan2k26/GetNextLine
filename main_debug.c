#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*archive;
	fd = open("ficheros/fichero", O_RDONLY);
	if (fd == -1)
	{
		printf("(%d)Error al abrir el archivo.\n", fd);
		return (0);
	}
	archive = get_next_line(fd);
	while (archive)
	{
		printf("\n\n\tArchivo: \n%s", archive);
		archive = get_next_line(fd);
	}
	system("\nleaks gnl.out");
    close(fd);
	return (0);
}
