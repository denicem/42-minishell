/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:35:21 by fquist            #+#    #+#             */
/*   Updated: 2022/03/10 16:11:17 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	valid_exit(void)
{
	write(2, "exit\n", 5);
	free_env();
	exit(g_exit_status);
}

static int	exit_error(char *str, int r_value)
{
	t_stringbuilder	*sb;
	char			*err_msg;

	sb = sb_create();
	sb_append_str(sb, "exit: ");
	sb_append_str(sb, str);
	sb_append_str(sb, ": numeric argument required");
	err_msg = sb_get_str(sb);
	sb_destroy(sb);
	error_msg(err_msg, r_value);
	free(err_msg);
	return (r_value);
}

static bool	check_valid_arg(char *arg)
{
	if (!*arg || (*arg != '+' && *arg != '-' && !ft_is_digit(*arg)))
		return (false);
	arg++;
	while (*arg)
	{
		if (!ft_is_digit(*arg))
			return (false);
		arg++;
	}
	return (true);
}

void	ft_exit(t_table *table)
{
	if (!ft_strcmp(table->exe, "exit"))
	{
		if (get_arr_size(table->cmd_arr) > 0)
		{
			if (ft_is_alpha(**table->cmd_arr)
				|| get_arr_size(table->cmd_arr) == 1)
			{
				if (check_valid_arg(*table->cmd_arr))
					g_exit_status = ft_atoi(*table->cmd_arr);
				else
					g_exit_status = exit_error(*table->cmd_arr, 255);
				free_table(&table);
				valid_exit();
			}
			g_exit_status = error_msg("exit: too many arguments", FAIL);
			return ;
		}
		g_exit_status = SUCCESS;
		free_table(&table);
		valid_exit();
	}
}
