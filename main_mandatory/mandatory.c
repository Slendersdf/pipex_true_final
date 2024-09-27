#include "../src/pipex.h"

int main (int ac, char **av, char **env)
{
	/* (void)ac;
	(void)av;
	char *result;

	// Test de parse_path
	printf("=== Test parse_path ===\n");
	result = parse_path("/usr/bin:/bin:/usr/local/bin", "ls");
	printf("Expected: /usr/bin/ls\n");
	printf("Result:   %s\n", result);
	free(result);

	result = parse_path("/usr/local/bin:/usr/bin:/bin", "cat");
	printf("Expected: /usr/local/bin/cat\n");
	printf("Result:   %s\n", result);
	free(result);

	// Test de get_path
	printf("\n=== Test get_path ===\n");
	result = get_path(env, "ls");
	printf("Command 'ls' found at: %s\n", result);

	result = get_path(env, "cat");
	printf("Command 'cat' found at: %s\n", result);

	result = get_path(env, "nonexistent_command");
	printf("Non-existent command should return input: %s\n", result); */

	// Test de la fonction exe
	/* printf("=== Test exe ===\n");
	char *cmd1[] = {"ls", "-l", NULL};
	exe(cmd1, env); */

	// Test de la fonction run
	printf("=== Test run ===\n");
	if (ac != 2)
	{
		printf("Usage: %s <command>\n", av[0]);
		return (1);
	}
	run(av[1], env);

	return 0;
}
