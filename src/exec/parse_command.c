/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:30:42 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/04 19:19:45 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_rdr(char *str)
{
	if (!str)
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (is_charset(*str, "<>"))
		return (1);
	else if (!ft_strncmp(str, "&>", 2))
		return (1);
	else
		return (0);
}

static void	make_cmds(t_args *args)
{
	int	cmd_idx;

	cmd_idx = 0;
	while (args->cmd[cmd_idx].params)
	{
		if (!check_builtin(&args->cmd[cmd_idx], args->cmd[cmd_idx].params[0]))
		{
			check_cmd_validity(args, &args->cmd[cmd_idx],
				args->cmd[cmd_idx].params[0]);
			args->cmd[cmd_idx].exec_f.exec = execve;
		}
		else
			update_builtin_func(&args->cmd[cmd_idx]);
		cmd_idx++;
	}
}

static void	merge_seperated_cmd(char **cmd_arr, t_cmds *cur, int cmd_idx)
{
	char	*tmp;

	tmp = ft_strjoin(cmd_arr[cmd_idx], " ");
	free(cmd_arr[cmd_idx]);
	cmd_arr[cmd_idx] = ft_strjoin(tmp, cur->cmd);
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
}

static char	**cmdlst_to_cmdarr(t_cmds *cmds, t_args *args)
{
	t_cmds	*cur;
	char	**cmd_arr;
	int		cmd_idx;

	cur = cmds;
	cmd_arr = (char **)ft_calloc(args->cnt + 1, sizeof(char *));
	cmd_idx = 0;
	while (cur && cur->cmd[0] != ';')
	{
		if (cur->cmd[0] != '|' && !is_rdr(cur->cmd))
			merge_seperated_cmd(cmd_arr, cur, cmd_idx);
		else if (cur->cmd[0] == '|')
			cmd_idx++;
		cur = cur->next;
	}
	return (cmd_arr);
}

void	build_structure(t_cmds *cmdlst, char ***envp, t_args *args)
{
	char	*tmp;
	char	**cmds;
	int		flag;

	flag = 0;
	tmp = ft_get_envp(*envp, "PATH");
	if (!tmp || !*tmp)
	{
		tmp = ft_strdup(".");
		flag = 1;
	}
	args->env_path = ft_split(tmp, ':');
	if (flag)
		free(tmp);
	args->envp = *envp;
	cmds = cmdlst_to_cmdarr(cmdlst, args);
	get_params(args, cmds, cmdlst);
	if (args->e_flag == 0)
		make_cmds(args);
	free_double_ptr((void ***)&cmds);
}
