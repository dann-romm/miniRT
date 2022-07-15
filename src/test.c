#include "parser.h"
#include <stdio.h>

int	main()
{
	int	err;

	err = parse_map("/Users/zaira/Desktop/miniRT/scene_test.rt");
	if (err != 0)
	{
		perror("parsing map");
		return (-1);
	}
	return (0);
}
