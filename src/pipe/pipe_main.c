/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@42student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:22:10 by jun               #+#    #+#             */
/*   Updated: 2021/09/11 10:36:11 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	exec_cmd_main(char **cmds, char **envp)
{
	int		cmd_end;
	int		cmd_cnt;
	t_args	*args;

	cmd_cnt = 0;
	cmd_end = 0;
	while (cmds[cmd_end])
	{
		if (!ft_strncmp(cmds[cmd_end], ";", 2))
		{
			args = (t_args *)ft_calloc(1, sizeof(t_args));
			args->cnt = cmd_cnt;
			build_structure(cmds, envp, args);
			breed_process(args);
//			free_structure();
			cmd_cnt = 0;
		}
		if (ft_strncmp(cmds[cmd_end], "|", 2))
			cmd_cnt++;
		cmd_end++;
	}
	return (EXIT_SUCCESS);
}
