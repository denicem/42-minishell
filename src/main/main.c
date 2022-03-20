/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/20 03:15:36 by nelix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_builtin(t_table *table)
{
	if (!ft_strcmp(table->exe, "pwd")
		|| !ft_strcmp(table->exe, "cd")
		|| !ft_strcmp(table->exe, "echo")
		|| !ft_strcmp(table->exe, "export")
		|| !ft_strcmp(table->exe, "env")
		|| !ft_strcmp(table->exe, "exit")
		|| !ft_strcmp(table->exe, "unset"))
		return (true);
	return (false);
}

static int	check_empty_input(char *input)
{
	int	i;

	i = 0;
	while (check_whitespace(input[i]))
		i++;
	if (input[i] == '\0')
		return (1);
	else
		return (0);
}

char	*get_prompt(void)
{
	t_stringbuilder	*prompt;
	char			*path;
	char			*ret;

	prompt = sb_create();
	path = getcwd(NULL, 0);
	sb_append_str(prompt, CYAN);
	sb_append_str(prompt, ft_strrchr(path, '/'));
	sb_append_str(prompt, "\033[0;32m °º¤ø,¸,ø¤º°`°º¤ø(ಠ_ಠ)┌∩┐ ");
	sb_append_str(prompt, GREEN);
	sb_append_str(prompt, "@");
	sb_append_str(prompt, getenv("USER"));
	sb_append_str(prompt, "$ \e[0m");
	ret = sb_get_str(prompt);
	sb_destroy(prompt);
	free(path);
	ret = readline(ret);
	return (ret);
}

// cmds with quoted arguments not working (include whitespaces). 
// implement return values for cmds.
// implement signals
int	built_in_exec(t_table *table)
{
	if (table->log_op == 0 && table->exe && check_builtin(table))
	{
		if (!ft_strcmp(table->exe, "pwd"))
			ft_pwd();
		if (!ft_strcmp(table->exe, "cd"))
			ft_cd(table);
		if (!ft_strcmp(table->exe, "echo"))
			ft_echo(table);
		if (!ft_strcmp(table->exe, "export"))
			ft_export(table->args);
		if (!ft_strcmp(table->exe, "env"))
			ft_env();
		if (!ft_strcmp(table->exe, "exit"))
			ft_exit(table);
		if (!ft_strcmp(table->exe, "unset"))
			ft_unset(table);
		return (1);
	}
	return (0);
}

static void	bitchy_snake_shell(t_node **head, t_table **table)
{
	char	*read;
	int		s_out = dup(STDOUT_FILENO);
	int		s_in = dup(STDIN_FILENO);

	print_header();
	// system("(afplay mp3/welcome.mp3&)");
	// system("(afplay mp3/snake.mp3&)");
	// system("afplay mp3/error2.mp3");
	while (true)
	{
		read = get_prompt();
		if (read != NULL && ft_strcmp(read, ""))
		{
			add_history(read);
			if (!check_empty_input(read))
			{
				lexer(head, read);
				// print_nodes(*head);
				expander(head);
				// print_nodes(*head);
				parser(head, table);
				print_cmd_table(*table);
				exec_loop(*table);
			}
			free_node(head);
			free_table(table);
			// system("leaks minishell");
		}
		free(read);
		dup2(s_in, STDIN_FILENO);
		dup2(s_out, STDOUT_FILENO);
	}
}

int	main(int argc, char *argv[], char **environ)
{
	t_node	*head;
	t_table	*table;

	(void) argc;
	(void) argv;
	head = NULL;
	table = NULL;
	get_env(environ);
	bitchy_snake_shell(&head, &table);
	return (0);
}
