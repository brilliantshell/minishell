/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:06:28 by ghan              #+#    #+#             */
/*   Updated: 2021/09/26 18:15:43 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern int	g_exit_code;

t_cmds	*parse_line_main(char *ln_read, char **ft_envp)
{
	t_cmds	*ret;
	t_cmds	*cmds_hd;
	char	*one_ln;

	one_ln = ft_strdup("");
	if (!read_internal_prompt(&one_ln, ln_read, 0))
	{
		if (g_exit_code == -42)
			g_exit_code = GEN_ERR;
		free(one_ln);
		return (NULL);
	}
	sub_env(&one_ln, ft_envp);
	cmds_hd = ps_lst_init(NULL);
	split_by_symbols(cmds_hd, one_ln);
	if (!check_smcol_pipe_syntax(cmds_hd->next)
		|| !check_rdr_syntax(cmds_hd->next))
	{
		g_exit_code = 258;
		free_cmds_lst(&cmds_hd);
		return (NULL);
	}
	ret = cmds_hd->next;
	free(cmds_hd);
	return (ret);
}
