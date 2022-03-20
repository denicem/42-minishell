/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:40:37 by fquist            #+#    #+#             */
/*   Updated: 2022/03/11 23:00:49 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_redir_token(t_node **node, char **input)
{
	t_type	type;

	type = (*node)->type;
	while (check_redir(**input) || check_whitespace(**input))
		(*input)++;
	append_token(&(*node)->tokens, new_token(get_word(input), type));
	return (1);
}

int	create_tokens(t_node **node, char **input)
{
	int		cmd_present;
	t_type	type;

	if (check_redir((*node)->type))
		create_redir_token(node, input);
	else
	{
		cmd_present = 0;
		while ((**input && !check_metachar(**input)))
		{
			if (!(cmd_present++))
				type = COMMAND;
			else if (**input == '-')
				type = OPTION;
			else
				type = ARG;
			append_token(&(*node)->tokens, new_token(get_word(input), type));
			while (check_whitespace(**input))
				(*input)++;
		}
	}
	return (1);
}

int	define_type(char *input)
{
	if (input[0] == LPAREN || input[0] == RPAREN)
		return (input[0]);
	if (check_metachar(input[0]))
	{
		if (input[0] == input[1])
			return (input[0] * 4);
		else
			return (input[0]);
	}
	return (COMMAND);
}

int	lexer(t_node **head, char *input)
{
	t_node	*new;

	while (*input)
	{
		if (check_whitespace(*input))
		{
			input++;
			continue ;
		}
		new = append_node(head, new_node());
		new->type = define_type(input);
		if (new->type == AND || new->type == OR)
			input += 2;
		else if (new->type == COMMAND || check_redir(new->type))
			create_tokens(&new, &input);
		else
			input++;
	}
	return (1);
}