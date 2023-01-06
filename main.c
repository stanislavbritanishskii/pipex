/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:19:59 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/07 00:34:06 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *join_three_lines(char *str1, char *str2, char *str3)
{
	char *res;
	char *mid_res;

	mid_res = ft_strjoin(str1, str2);
	res = ft_strjoin(mid_res, str3);
	free(mid_res);
	return (res);
}

char	**get_paths(char **env)
{
	int		i;
	char	**mid_res;

	i = -1;
	mid_res = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			mid_res = ft_split(&env[i][5], ":");
	}
	return (mid_res);
}

char	*valid_path(char **paths, char *filename)
{
	char	*full_path;
	char	*path_with_slash;
	int		i;

	i = -1;
	if (!access(filename, X_OK))
		return(filename);
	while(paths[++i])
	{
		path_with_slash = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_with_slash, filename);
		free(path_with_slash);
		if (!access(full_path, X_OK))
			return(full_path);
		free(full_path);
	}
	return(NULL);
}
// input "cmd1 arg1 arg2" cmd2 cmd3 output

void checkleaks()
{
	system("leaks pipex");
}



//dup2(new value, old variable)

int **make_truby(int n)
{
	int **res;
	int	i;

	res = malloc(sizeof(int *) * (n + 1));
	i = 0;
	while(i < n)
	{
		res[i] = malloc(sizeof(int) * 2);
		pipe(res[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void close_truby(int **truby, int cur, int len)
{
	int i;

	i = 0;
	if (cur == 0)
		close(truby[0][0]);
	else if (cur == len)
		close(truby[len - 1][1]);
	else
	{
		close(truby[cur - 1][1]);
		close(truby[cur][0]);
	}
	while (truby[i])
	{
		if (cur < i || cur > i + 1)
		{
			close(truby[i][0]);
			close(truby[i][1]);
		}
		i++;
	}
}

void plumber(int **truby)
{
	int	i;
	i = 0;
	while(truby[i])
	{
		close(truby[i][1]);
		close(truby[i][0]);
		free(truby[i]);
		i++;
	}
	free(truby);
}

pid_t	*make_pids(int n)
{
	pid_t *res;
	res = malloc(sizeof(pid_t) * n);
	return (res);
}

void waitress(pid_t *pids, int len)
{
	while(len)
		waitpid(pids[--len], NULL, 0);
}

char **transform_args_to_cmds(char **argv)
{
	char **res;
	int	i;
	
	i = 0;
	while(argv[i++])
		;
	i = i - 3;
	i = i - (!ft_strncmp(argv[1], "here_doc\0", 9));
	res = malloc(sizeof(char *) * i);
	i = 0;
	if ((!ft_strncmp(argv[1], "here_doc\0", 9)))
	{
		res[0] = join_three_lines(argv[1], " ", argv[2]);
		i++;
	}
	while (argv[i + 3])
	{
		res[i] = argv[i + 2];
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	dups(int fd1, int fd2)
{
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
}

int	main(int argc, char **argv, char **env)
{
	char **paths;
	int **truby;
	int fd;
	int fd2;
	int number_of_children;
	int number_of_pipes;
	pid_t *pids;
	int	here_doc;
	int i;
	char **cmds;

	// atexit(&checkleaks);
	if (argc < 5)
		return (0);
	cmds = transform_args_to_cmds(argv);
	here_doc = !ft_strncmp(cmds[0], "here_doc", 8);
	number_of_children = argc - 3;
	number_of_pipes = number_of_children - 1;
	truby = make_truby(number_of_pipes);
	pids = make_pids(number_of_children);
	fd = open(argv[1], O_RDONLY);
	i = 0;
	if (!here_doc)
		fd2 = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	else
	{
		fd2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
		char **args = ft_split(cmds[0], " "); 
		read_from_to(args[1], STDIN_FILENO, truby[0][1], number_of_pipes);
		ft_split_clear(args);
		i++;
	}
	paths = get_paths(env);
	while (i <= number_of_pipes)
	{
		pids[i] = fork();
		if (!pids[i])
		{
			if (i == 0)
				dups(fd, truby[0][1]);
			else if (i == number_of_children - 1)
				dups(truby[i-1][0], fd2);
			else
				dups(truby[i - 1][0], truby[i][1]);
			close_truby(truby, i, number_of_pipes);
			char **args = ft_split(cmds[i], " ");
			char *path = valid_path(paths, args[0]); 
			if(!path)
			{
				ft_putstr_fd("commmand not found: ", STDERR_FILENO);
				ft_split_clear(args);
				free(path);
				exit (1);
			}
			execve(path, args, env);
		}
		i++;
	}
	plumber(truby);
	if (here_doc)
		free(cmds[0]); 
	free(cmds);
	waitress(pids, number_of_children);
	close(fd);
	close(fd2);
	ft_split_clear(paths);
	free(pids);
	return (0);
}

