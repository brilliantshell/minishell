/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:30:15 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/12 10:13:41 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/* Include Libraries */

# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"
# include "builtin.h"
# include <readline/readline.h>

/* User Defines */

# define X_ERR 126
# define CMD_ERR 127
# define FMT_ERR 2

/* qm rm flags */

# define RM_CHAR -1
# define ADD_BS 2
# define SWAP_CSET " \t\n<>"

typedef struct s_cmds
{
	char			*cmd;
	struct s_cmds	*next;
}	t_cmds;

typedef enum e_info
{
	rd_from_file = 0,
	rd_heredoc,
	wr_to_file,
	wr_append,
	wr_output_to_file,
	dup_fd,
	close_fd,
	rdwr,
	error,
}	t_info;

typedef enum e_builtin
{
	notbuiltin = 0,
	is_echo,
	is_cd,
	is_pwd,
	is_exprt,
	is_unset,
	is_env,
	is_ext,
}	t_builtin;

typedef struct s_rdr
{
	t_info			info;
	char			*file;
	int				fd[2];
	char			*limiter;
	struct s_rdr	*next;
}	t_rdr;

typedef union u_exec_f
{
	int		(*exec)(const char *, char *const [], char *const []);
	int		(*exec_env)(const char *, char *const [], char ***const);
}	t_exec_f_u;

typedef struct s_cmd
{
	pid_t			pid;
	int				pipe_fd[2];
	t_builtin		builtin;
	t_exec_f_u		exec_f;
	char			**params;
	t_rdr			*rdr;
}	t_cmd;

typedef struct s_args
{
	int				cnt;
	int				e_flag;
	char			**env_path;
	char			**envp;
	t_cmd			*cmd;
}	t_args;

/* FUNCTIONS */

/* Signal handler in pipe */

void	signal_handle_wo_rl_prompt(int signal);
void	signal_heredoc(int sig);
void	sigint_n_sigquit_handler(void (*sigfunction));
void	reset_signal(int sig);
void	multi_shell_erase_newline(int sig);
void	no_newline_for_sigquit(int sig);

/* Check Validity */

void	check_cmd_validity(t_args *args, t_cmd *cmd, char *param);
t_ll	check_exit_arg_validity(char **argv);

/* Check Builtin */

int		check_builtin(t_cmd *cmd, char *cmds);
void	update_builtin_func(t_cmd *cmd);

/* Redirecting */

void	get_rdr_info(char *rdrs, t_cmd *cmd);
void	connect_pipestream(t_args *args, int idx);
void	destroy_pipe(int *pipe_fd);
int		redirect_stream(t_cmd *cmd);
int		is_rdr(char *str);

/* Preprocessing */

void	build_structure(t_cmds *cmdlst, char ***envp, t_args *args);
void	get_params(t_args *args, char **cmds, t_cmds *cmdlst);
void	execute_subshell_main(t_args *args, int idx);
void	execute_builtin(t_args *args, char ***ft_envp);

/* Handle exit code */

int		wstatus(int status);
int		wifexited(int status);
int		wifsignaled(int status);
int		wexitstatus(int status);
int		wtermsig(int status);
void	wait_process(t_args *args);
int		get_exit_status(int status);

/* Redirection in builtin */

int		**backup_fd(t_rdr *rdr);
void	retrieve_fd(int **fds);

/* File Stat */

int		s_isdir(int mode);

/* Sub_env  & rm qm */

void	sub_env(char **params, char **ft_envp);
void	skip_qm(char *str, int *i, char *charset);
void	rm_unnecessary_qm(char **param);
void	rm_or_expand_qm(char **param, int *cp_flag, size_t len, size_t add);
char	*strndup_with_flag(char *s1, int *flag, size_t n, size_t add);
char	*strchr_skip_bslash(char *s, int c);
int		check_valid_rdr_symbols(char *s, int i);
void	flag_qm(char *s, int *i, int *cp_flag, size_t *add_cnt);
size_t	flag_add_cnt(char *s, int *cp_flag, int fst, int len);
void	env_parse_quote(char **env);
int		end_by_esc(char **one_ln);

/* Utils */

int		get_wspace_len(char *str, char *charset, char ign, int cnt);
int		make_string(char *cmdset, t_cmd *cmd, int p_idx, int len);
char	*ft_substr_wo_chr(char *str, unsigned int start, size_t len, char c);
void	free_arg_structure(t_args *args);
void	free_double_ptr(void ***ptr);
int		get_wspace_idx(char *str, char *charset, char ign);
char	*ft_get_envp(char **ft_envp, char *var);

#endif
