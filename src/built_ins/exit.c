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

void	ft_exit(t_table *table)
{
	if (!ft_strcmp(table->exe, "exit"))
	{
		// free stuff
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
}