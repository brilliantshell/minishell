/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:30:42 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/26 13:42:44 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static int	check_builtin(t_args *args, char *cmds)
{
	int	is_builtin;

	is_builtin = 1;
	if (!ft_strcmp("echo", cmds))
		args->cmd->builtin = is_echo;
	else if (!ft_strcmp("cd", cmds))
		args->cmd->builtin = is_cd;
	else if (!ft_strcmp("pwd", cmds))
		args->cmd->builtin = is_pwd;
	else if (!ft_strcmp("export", cmds))
		args->cmd->builtin = is_exprt;
	else if (!ft_strcmp("unset", cmds))
		args->cmd->builtin = is_unset;
	else if (!ft_strcmp("env", cmds))
		args->cmd->builtin = is_env;
	else if (!ft_strcmp("exit", cmds))
		args->cmd->builtin = is_ext;
	else
	{
		args->cmd->builtin = notbuiltin;
		is_builtin = 0;
	}
	return (is_builtin);
}

void	update_builtin_func(t_cmd *cmd)
{
	if (cmd->builtin == is_echo)
		cmd->exec = echo;
	else if (cmd->builtin == is_cd)
		cmd->exec = cd;
	else if (cmd->builtin == is_pwd)
		cmd->exec = pwd;
//	else if (cmd->builtin == is_exprt)
//		cmd->exec = exprt;
//	else if (cmd->builtin == is_unset)
//		cmd->exec = unset;
	else if (cmd->builtin == is_env)
		cmd->exec = env;
	else if (cmd->builtin == is_ext)
		cmd->exec = ext;
}

static void	make_cmds(t_args *args)
{
	int	cmd_idx;

	cmd_idx = 0;
	while (args->cmd[cmd_idx].params)
	{
		if (!check_builtin(args, args->cmd[cmd_idx].params[0]))
		{
			check_cmd_validity(args, &args->cmd[cmd_idx],
				args->cmd[cmd_idx].params[0]);
			args->cmd[cmd_idx].exec = execve;
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

void	build_structure(t_cmds *cmdlst, char **envp, t_args *args)
{
	int		idx;
	char	*tmp;
	char	**cmds;

	idx = 0;
	tmp = ft_get_envp(envp, "PATH");
	if (!tmp)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	args->env_path = ft_split(tmp, ':');
	args->envp = envp;
	cmds = cmdlst_to_cmdarr(cmdlst, args);
	get_params(args, cmds, cmdlst);
	make_cmds(args);
}