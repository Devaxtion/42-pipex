/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:41:06 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/02 16:07:49 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// open, close, read, write
// access, dup, dup2, execve
// fork, pipe, unlink
# include <unistd.h>

// O_RDONLY, O_CREAT, O_WRONLY, O_TRUNC
# include <fcntl.h>

// malloc, free, exit
# include <stdlib.h>

// perror + strerror + errno
# include <stdio.h>
# include <string.h>
# include <errno.h>

// wait, waitpid
# include <sys/wait.h>

// Libft
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// Errors
# define ERR_NO_PERMS 1
# define ERR_INVALID_ARGS 2
# define ERR_CANT_OPEN_IN 3
# define ERR_CANT_OPEN_OUT 4
# define ERR_CANT_FIND_CMD 127
# define ERR_CANT_GET_PATH_ENVP 6
# define ERR_ALLOC 7
# define ERR_CMD_EMPTY 127
# define ERR_PIPE_FAIL 9
# define ERR_FORK_FAIL 10
# define ERR_EXECVE_FAIL 127

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
	char	**av;
	char	**envp;
	int		pipefd[2];
	int		pids[2];
	int		pstatus[2];
}			t_pipex;

// Exit
void	free_str_array(char **array);
void	free_cmd(t_cmd *cmd);
void	cleanup_and_exit(int status_code, const char *error_msg, t_pipex *data);

// Utils
void	close_pipe(int pipefd[2]);
char	**get_path_envp(char **envp);
int		find_prefix_in_array(char **array, char *prefix);
int		find_word_in_array(char	**array, char *word);

// Commands
void	parse_single_cmd(char *cmd_str, t_cmd *cmd, t_pipex *data);
void	parse_fake_cmd(t_cmd *cmd, t_pipex *data);

// Execute
void	run_command(int in_fd, int out_fd, t_cmd cmd, t_pipex *data);
int		get_exit_status(int primary_status, int fallback_status);

// Childs
void	create_childs(t_pipex *data);
void	wait_for_childs(int pids[2], int status[2]);

#endif