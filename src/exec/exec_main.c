/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:22:10 by jun               #+#    #+#             */
/*   Updated: 2021/10/10 20:49:08 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int	g_exit_code;

static void	process_to_execute(t_cmds *cmds, char ***envp, int cmd_cnt)
{
	t_args	*args;

	args = (t_args *)ft_calloc(1, sizeof(t_args));
	args->envp = *envp;
	args->cnt = cmd_cnt;
	args->e_flag = 0;
	args->cmd = (t_cmd *)ft_calloc(args->cnt + 1, sizeof(t_cmd));
	build_structure(cmds, envp, args);
	if (args->e_flag == 0)
	{
		if (args->cnt == 1 && args->cmd[0].builtin != notbuiltin)
			execute_builtin(args, envp);
		else
			execute_subshell_main(args, 0);
	}
	free_arg_structure(args);
}

static t_cmds	*seperate_cmd(t_cmds *cmds, char ***envp,
		t_cmds *cur, int *cmd_cnt)
{
	if (cur->cmd[0] == ';' || !cur->next)
	{
		process_to_execute(cmds, envp, *cmd_cnt);
		cmds = cur->next;
		*cmd_cnt = 1;
	}
	else if (cur->cmd[0] == '|')
		*cmd_cnt += 1;
	return (cmds);
}

int	exec_cmd_main(t_cmds *cmdlst, char ***envp)
{
	t_cmds	*cur;
	t_cmds	*start;
	int		cmd_cnt;

	sigint_n_sigquit_handler(signal_handle_wo_rl_prompt);
	signal(SIGUSR1, no_newline_for_sigquit);
	start = cmdlst;
	cur = start;
	cmd_cnt = 1;
	while (cur)
	{
		start = seperate_cmd(start, envp, cur, &cmd_cnt);
		cur = cur->next;
	}
	return (EXIT_SUCCESS);
}
