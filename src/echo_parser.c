/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 03:09:51 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/11 00:41:43 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	is_echo_opt_valid(char *opt)
{
	int	i;

	i = 0;
	if (opt[i++] != '-')
		return (false);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int echo_parser(t_token *help, t_table **new) // FIXME: it segfaults, when the env var doesn't exist.
{
	bool	echo_opt_valid;

	echo_opt_valid = is_echo_opt_valid(help->name);
	if (echo_opt_valid)
	{
		(*new)->args = ft_strdup("-n");
		help = help->next;
		while (help)
		{
			if (!ft_strcmp(help->name, "-n"))
			{
				help = help->next;
				continue ;
			}
			else
				break ;
		}
		while (help)
		{
			if (*help->name == '$')
				(*new)->args = str_join((*new)->args, " ", get_env_var(help->name + 1));
			else
				(*new)->args = str_join((*new)->args, " ", help->name);
			help = help->next;
		}
	}
	else
	{
		if (*help->name == '$')
				(*new)->args = ft_strdup(get_env_var(help->name + 1));
		else
			(*new)->args = ft_strdup(help->name);
		help = help->next;
		while (help)
		{
			if (*help->name == '$')
				(*new)->args = str_join((*new)->args, " ", get_env_var(help->name + 1));
			else
				(*new)->args = str_join((*new)->args, " ", help->name);
			help = help->next;
		}
	}
	return (1);
}
