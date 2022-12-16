#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av, char **envp)
{
	char	*path = "/bin/";
	char	*argv[] = {path, "-c", "echo $TEST", NULL};
	// char	*envp[] = {"TEST=hello", NULL};

	execve(path, argv, envp);
}