/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:41:06 by leramos-          #+#    #+#             */
/*   Updated: 2025/11/20 13:23:03 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// open, close, read, write
// access, dup, dup2, execve
// fork, pipe, unlink
# include <unistd.h>

// malloc, free, exit
# include <stdlib.h>

// perror + strerror
# include <stdio.h>
# include <string.h>

// wait, waitpid
# include <sys/wait.h>

// Libft
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// Errors
# define ERR_INVALID_ARGUMENTS 1
# define ERR_CANT_OPEN_IN 2
# define ERR_CANT_OPEN_OUT 3

// FDs

# define FD_STDIN 0
# define FD_STDOUT 1

// Structs
typedef struct s_cmd
{
	char	*path;
	char	**args;
}			t_cmd;

typedef struct s_pipex
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	int		in_fd;
	int		out_fd;
}			t_pipex;

// Exit
void	cleanup_and_exit(int status_code, const char *error_msg, t_pipex *data);

// Utils
char	**get_path_envp(char **envp);
void	print_array(char **array, char *name);
int		find_prefix_in_array(char **array, char *prefix);
int		find_word_in_array(char	**array, char *word);

// Parsing
void	parse_cmds(t_pipex *data, char **av, char **envp);

// Execute
void	execute_pipex(t_pipex data, char **envp);

#endif