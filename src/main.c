/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:34 by ghan              #+#    #+#             */
/*   Updated: 2021/09/25 21:26:21 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char *argv[], char *envp[])
{
	char	*line_read;
	char	**ft_envp;
	t_cmds	*cmdlst;

	ft_envp = esh_pre_process(argc, argv, envp);
	while (1)
	{
		unexp_eof_sig_handler();
		line_read = readline("🐘 esh > ");
		eof_exit(line_read);
		add_history(rl_line_buffer);
		cmdlst = parse_line_main(line_read, ft_envp);
		if (cmdlst && cmdlst->cmd && *cmdlst->cmd)
			exec_cmd_main(cmdlst, ft_envp);
		sigint_n_sigquit_handler(main_sig_handler);
		free_cmds_lst(&cmdlst);
		free(line_read);
	}
	return (EXIT_SUCCESS);
}
