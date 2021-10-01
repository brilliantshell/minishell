/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diy_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 20:30:17 by ghan              #+#    #+#             */
/*   Updated: 2021/10/01 20:45:21 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_envp(char **ft_envp, char *var)
{
	int	set_len;
	int	eq_idx;
	int	i;

	set_len = ft_strsetlen(ft_envp);
	i = -1;
	while (++i < set_len)
	{
		if (ft_strchr(ft_envp[i], '='))
		{
			eq_idx = ft_strchr(ft_envp[i], '=') - ft_envp[i];
			if (!ft_strncmp(ft_envp[i], var, eq_idx))
				return (ft_envp[i] + eq_idx + 1);
		}
		else if (!ft_strcmp(ft_envp[i], var))
			return (ft_envp[i] + ft_strlen(ft_envp[i]));
	}
	return (NULL);
}

char	**dup_envp(char *envp[], int set_len)
{
	char	**ret;
	int		i;

	ret = (char **)ft_calloc(set_len + 1, sizeof(char *));
	i = -1;
	while (++i < set_len)
		ret[i] = ft_strdup(envp[i]);
	return (ret);
}
