/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:48:10 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/08 12:01:01 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ====== LIBRARIES ====== */
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include "../lib42/lib42.h"

/* ====== TEXT STYLING ====== */
# define GY "\033[1;30m"
# define BL "\033[5;34m"
# define YL "\033[1;33m"
# define GN "\033[1;32m"
# define DEF "\033[0m"

/* ====== MACROS ====== */
# define OPERATORS "<>|"
# define BUILTINS_TOTAL 7
# define BUFFSIZE 256

/* ====== ENUMS ====== */

typedef enum e_token_type
{
	CMD,
	EXT_CMD,
	OPR,
	ID,
	VAL,
	LIT
}		t_token_type;

typedef enum e_operators
{
	DOLLAR,
	RDRIN,
	RDROUT,
	HEREDOC,
	APPEND,
	PIPE,
	ASSG
}		t_operators;

/* ====== STRUCTS ====== */
typedef struct s_token
{
	t_token_type	type;
	void			*content;
}		t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
}		t_env;

typedef struct s_minishell
{
	char	*prompt;
	char	**builtins;
	t_list	*envp;
}		t_minishell;

/* ====== FUNCTION PROTOTYPES ====== */

void	init_minishell(t_minishell *ms, char **ev);
void	init_environment(t_minishell *ms, char **ev);
void	init_signal();
void	add_env_var(t_minishell *ms, char *key, char *value);

void	lexer(t_minishell *ms, char *cmds);
void	tokenizer(t_minishell *ms, char *word);
void	recognize_cmd(t_minishell *ms, char *token);

int		call_cd(t_list *envp, char *args);
// int		call_pwd(char *args);
// int		call_env(char **envp);

t_env	*load_env_var(t_list *envp, char *var);
void	edit_env_val(t_list *envp, char *var, char *value);
char	*get_env_value(t_minishell *ms, char *key);

#endif