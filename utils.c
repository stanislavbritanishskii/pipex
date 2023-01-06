/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:08:19 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/07 00:12:06 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *repeat_line_n_times(char *str, int n)
{
	char *res;
	char *mid_res;

	n = n - 1;
	if (n <= 0)
		return ("");
	res = ft_strdup(str);
	n--;
	while (n)
	{
		mid_res = ft_strjoin(res, str);
		free(res);
		res = ft_strdup(mid_res);
		free(mid_res);
		n--;
	}
	return (res);
}

void	read_from_to(char* delimimter, int input_fd, int output_fd, int number_of_pipes)
{
	char *buf;
	char *pipes;

	pipes = repeat_line_n_times("pipe ", number_of_pipes);
	ft_putstr_fd(pipes, input_fd);
	ft_putstr_fd("heredoc> ", input_fd);
	buf = get_next_line(input_fd);
	while (ft_strncmp(buf, delimimter, ft_strlen(buf) - 1) || ft_strlen(buf) == 1)
	{
		ft_putstr_fd(pipes, input_fd);
		ft_putstr_fd("heredoc> ", input_fd);
		ft_putstr_fd(buf, output_fd);
		free(buf);
		buf = get_next_line(input_fd);
	}
	free(pipes);
	free(buf);
}
