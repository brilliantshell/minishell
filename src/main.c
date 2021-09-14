/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:34 by ghan              #+#    #+#             */
/*   Updated: 2021/09/13 09:01:26 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	signal_handler(int signal)
{

	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (signal == SIGQUIT)
		rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line_read;
	char	**cmds;

	if (argc > 1 || argv[1])
		is_error(NULL, NULL, "esh does not receive arguments", EXIT_FAILURE);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		line_read = readline("🐘 esh > ");
		if (!line_read || !ft_strncmp(line_read, "exit", 4))
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		add_history(rl_line_buffer);
		cmds = parse_line_main(line_read);
		/* NOTE : Do we need error_code here? */
		envp = 0;
		// if (cmds)
		// 	exec_cmd_main(cmds, envp);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		free_cmds(cmds);
		free(line_read);
	}
	return (EXIT_SUCCESS);
}
