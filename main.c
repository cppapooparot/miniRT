#include "inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_scene scene;

	if (argc != 2)
	{
		ft_putstr_fd("miniRT: Invalid input\n"
						"Usage: ./miniRT path/to/[scene].rt\n",
						2);
		return (1);
	}
	if (!initialize_scene(argv[1], &scene))
		return (1);
	return (0);
}