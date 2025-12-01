/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:37:06 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/01 14:12:13 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ./pipex infile cmd1 cmd2 outfile
int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	int		status;

	if (ac != 5)
		cleanup_and_exit(ERR_INVALID_ARGS, "Use: infile c1 c2 outfile", NULL);
	init_data(&data);
	open_files(&data, av);
	parse_args(&data, av, envp);
	status = execute_pipex(&data, envp);
	cleanup_and_exit(status, NULL, &data);
	return (0);
}
