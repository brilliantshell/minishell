/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:06:28 by ghan              #+#    #+#             */
/*   Updated: 2021/09/10 18:06:29 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	*strchr_skip_bslash(const char *s, int c)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (*str != (unsigned char)c && (*str != '\0'))
	{
		if (*str == '\\')
			str++;
		if (*str != '\0')
			str++;
	}
	if (*str != (unsigned char)c)
		return (NULL);
	return ((char *)str);
}

static void	is_qmbt(char *one_ln, char **qmbt)
{
	*qmbt = strchr_skip_bslash(one_ln, '`');
	if (!(*qmbt) || (strchr_skip_bslash(one_ln, '\'')
			&& *qmbt > strchr_skip_bslash(one_ln, '\'')))
		*qmbt = strchr_skip_bslash(one_ln, '\'');
	if (!(*qmbt) || (strchr_skip_bslash(one_ln, '"')
			&& *qmbt > strchr_skip_bslash(one_ln, '"')))
		*qmbt = strchr_skip_bslash(one_ln, '"');
}

static int	cnt_skip_qmbt(char *one_ln, char *qmbt)
{
	size_t	i;
	int		cnt;

	cnt = 0;
	i = 0;
	while (qmbt && *(one_ln + i))
	{
		if (qmbt && *(one_ln + i) == '\\')
		{
			i++;
			if (*(one_ln + i) == *qmbt || *(one_ln + i) == '\\')
				i++;
		}
		if (*(one_ln + i) == *qmbt)
			cnt++;
		if (cnt && cnt % 2 == 0)
		{
			cnt = 0;
			i++;
			is_qmbt(one_ln + i, &qmbt);
		}
		if (*(one_ln + i) != '\0')
			i++;
	}
	return (cnt);
}

static int	check_line_end(char **one_ln, char *ln)
{
	char	*to_free;
	char	*qmbt;
	int		cnt;

	to_free = *one_ln;
	*one_ln = ft_strjoin(*one_ln, ln);
	free(to_free);
	is_qmbt(*one_ln, &qmbt);
	cnt = cnt_skip_qmbt(*one_ln, qmbt);
	if (cnt % 2 || !end_by_pipe(*one_ln, to_free) || !end_by_esc(*one_ln))
		return (0);
	return (1);
}

char	**complete_a_line(char **one_ln, char *ln_read)
{
	char	**cmds;
	char	*trim_ln;

	while (!check_line_end(one_ln, ln_read))
	{
		ln_read = readline("> ");
		if (!ln_read)
		{
			write(STDERR_FILENO,
				"🤣 esh: unexpected EOF while looking for matching `\"'\n", 56);
			free(*one_ln);
			*one_ln = ft_strdup("");
			break ;
		}
		add_history(rl_line_buffer);
	}
	trim_ln = ft_strtrim(*one_ln, " \t\n");
	cmds = split_by_pipe_sc(trim_ln, ";|");
	if (!cmds)
		is_error(NULL, NULL, "can't allocate memory", EXIT_FAILURE);
	free(trim_ln);
	free(*one_ln);
	*one_ln = ft_strdup("");
	return (cmds);
}