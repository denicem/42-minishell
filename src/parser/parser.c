/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/11 23:00:52 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void define_node(t_node *node, t_table **new)
{
	if (valid_name(&node->tokens) == SUCCESS)
	{
		if (check_redir(node->type))
			redir_parser(node->tokens, new);
		else if (node->type == COMMAND)
			command_parser(node->tokens, new);
	}
	else 
		printf("FAIL\n"); //temporary!!!
}

int	parser(t_node **node, t_table **table)
{
	create_cmd_table(node, table);
	return (0);
}

void	create_cmd_table(t_node **node, t_table **table)
{
	t_node	*curr_n;
	t_table	*new;

	curr_n = *node;
	if ((*node)->type == PIPE)
	{
		g_exit_status = error_msg("minishell: syntax error"
				"near unexpected token '|'\n", 258);
		return ;
	}
	while (curr_n)
	{
		new = append_table(table, new_table());
		if (check_log_op(curr_n->type))
		{
			new->log_op = curr_n->type;
			curr_n = curr_n->next;
			continue ;
		}
		while (curr_n && !check_log_op(curr_n->type))
		{
			define_node(curr_n, &new);
			curr_n = curr_n->next;
		}
	}
}
