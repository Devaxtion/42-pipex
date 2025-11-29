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
# define ERR_CANT_FIND_CMD 4
# define ERR_CANT_GET_PATH_ENVP 5
# define ERR_ALLOC 6
# define ERR_CMD_EMPTY 7

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
	char	**path_envp;
}			t_pipex;

// Exit
void	free_cmd(t_cmd *cmd);
void	cleanup_and_exit(int status_code, const char *error_msg, t_pipex *data);

// Utils
char	**get_path_envp(char **envp);
void	print_array(char **array, char *name);
int		find_prefix_in_array(char **array, char *prefix);
int		find_word_in_array(char	**array, char *word);

// Initializing
void	init_data(t_pipex *data);
void	open_files(t_pipex *data, char **av);
void	parse_args(t_pipex *data, char **av, char **envp);

// Execute
void	execute_pipex(t_pipex *data);

#endif