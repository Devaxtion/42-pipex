/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:37:06 by leramos-          #+#    #+#             */
/*   Updated: 2025/11/20 12:46:45 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ./pipex infile cmd1 cmd2 outfile
int	main(int ac, char **av, char **envp)
{
	t_pipex	data;

	if (ac != 5)
		cleanup_and_exit(ERR_INVALID_ARGUMENTS, "Correct parameters: infile cmd1 cmd2 outfile", NULL);
	init_data(&data);
	open_files(&data, av);
	parse_args(&data, av, envp);
	execute_pipex(&data);
	cleanup_and_exit(0, NULL, &data);
	return (0);
}
