/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/27 20:20:08 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	split_once(char *str, char *charset, char ign)
{
	int	idx;

	idx = 0;
	if (!str)
		return (0);
	if (!*str)
		return (0);
	while (is_charset(*(str + idx), charset))
	{
		printf("before :%s\n", &str[idx]);
		if (*(str + idx) == ign)
			idx++;
		if (!*(str + idx))
			break ;
		idx++;
	}
	while (!is_charset(*(str + idx), charset) && str[idx] != '\0')
	{
		printf("after : %s\n", &str[idx]);
		if (*(str + idx) == ign)
			idx++;
		if (!*(str + idx))
			break ;
		idx++;
	}
	return (idx);
}

static size_t	ft_strlen_wo_chr(char *str, int len, char c)
{
	size_t	cnt;

	cnt = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != '\\')
			cnt++;
		str++;
	}
	return (cnt);
}

char	*ft_substr_wo_chr(char *str, unsigned int start, size_t len, char c)
{
	size_t	idx;
	size_t	size;
	char	*ret;

	size = ft_strlen_wo_chr(&str[start], len, c);
	if (size >= len)
		return (ft_substr(str, start, len));
	idx = 0;
	ret = (char *)ft_calloc(size + 1, sizeof(char));
	while (idx < size && start <= len)
	{
		if (str[start] != '\\')
		{
			ret[idx] = str[start];
			idx++;
		}
		start++;
	}
	ret[idx] = '\0';
	return (ret);
}

int	make_string(char *cmdset, t_cmd *cmd, int p_idx)
{
	int		len;

	if (!ft_strcmp(cmdset, "\'\'") || !ft_strcmp(cmdset, "\"\""))
	{
		cmd->params[p_idx] = ft_strdup("");
		len = 2;
	}
	else if (is_charset(cmdset[0], "'"))
	{
		len = split_once(&cmdset[0], "'", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 1, len - 1, '\\');
	}
	else if (is_charset(cmdset[0], "\""))
	{
		len = split_once(&cmdset[0], "\"", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 1, len - 1, '\\');
	}
	else
	{
		len = split_once(&cmdset[0], "\t\n ", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 0, len, '\\');
	}
	return (len);
}
