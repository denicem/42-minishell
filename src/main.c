/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/01 23:33:32 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

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
	char	*str;
	char	*colorized;

	str = "\033[0;32m °º¤ø,¸,ø¤º°`°º¤ø(ಠ_ಠ)┌∩┐$ \e[0m";
	colorized = ft_strjoin(GREEN, ft_strrchr(getcwd(NULL, 0), '/'));
	return (readline(ft_strjoin(colorized, str)));
}

static void	bitchy_snake_shell(t_node **head, t_table **table, char **environ)
{
	char	*read;

	// (void)environ;
	(void)table;
	print_shell();
	while (true)
	{
		read = get_prompt();
		if (read != NULL && ft_strcmp(read, ""))
		{
			add_history(read);
			if (!check_empty_input(read))
			{
				// do stuff
				lexer(head, read);
				// print_nodes(*head);
				parser(head, table);
				// print_cmd_table(*table);
				// ft_pwd();
				// ft_cd(table, environ);
				// ft_exit(table);
				// ft_echo(table);
				ft_export(ft_env(environ), *table);
				// ft_env(environ);
			}
			free_table(table, false, false);
			free_list(head, false, false);
		}
	}
}

int	main(int argc, char *argv[], char **environ)
{
	t_node	*head;
	t_table	*names;
	t_table *table;

	(void)argc;
	(void)argv;
	// (void)environ;
	names = NULL;
	head = NULL;
	table = NULL;
	bitchy_snake_shell(&head, &table, environ);
	return (0);
}
