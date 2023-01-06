/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:19:57 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/06 23:33:16 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H



# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

void	read_from_to(char* delimimter, int input_fd, int output_fd, int number_of_pipes);

#endif