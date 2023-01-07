/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:19:59 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/07 04:09:49 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void checkleaks()
// {
// 	system("leaks pipex");
// }
// atexit(&checkleaks);

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_pipex	pipex;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 8) && argc < 6))
		return (0);
	i = pipex_init(&pipex, argv, argc, env);
	while (i <= pipex.number_of_pipes)
	{
		piping(&pipex, i, env);
		i++;
	}
	clean_pipex(&pipex);
	return (0);
}
