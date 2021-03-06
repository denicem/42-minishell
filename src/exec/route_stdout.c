/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:26:17 by fquist            #+#    #+#             */
/*   Updated: 2022/04/07 19:22:46 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	route_stdout(t_table *table, t_exec *fds)
{
	t_redir	*last_out;

	last_out = get_last_out_redir(table->redir);
	if (last_out)
	{
		if (last_redir_out(fds, last_out) < 0)
			return (-1);
	}
	else if (!last_out)
		handle_redir_out(table, fds);
	return (0);
}

int	last_redir_out(t_exec *fds, t_redir *last_out)
{
	if (last_out->type == GREAT)
	{
		fds->file_fd = open_file(last_out->file,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fds->file_fd < 0)
			return (-1);
		dup2(fds->file_fd, STDOUT_FILENO);
		close(fds->file_fd);
	}
	if (last_out->type == GREATGREAT)
	{
		fds->file_fd = open_file(last_out->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fds->file_fd < 0)
			return (-1);
		dup2(fds->file_fd, STDOUT_FILENO);
		close(fds->file_fd);
	}
	return (0);
}

void	handle_redir_out(t_table *table, t_exec *fds)
{
	{
		if (table->next == NULL)
		{
			if (fds->here_fd[READ] > 0 || fds->here_fd[WRITE] > 0)
			{
				dup2(fds->stout, fds->here_fd[WRITE]);
				close(fds->stout);
			}
			dup2(fds->stout, STDOUT_FILENO);
			close(fds->stout);
		}
		else
		{
			if (fds->here_fd[READ] > 0 || fds->here_fd[WRITE] > 0)
			{
				dup2(fds->fd[READ], fds->here_fd[WRITE]);
				close(fds->fd[READ]);
			}
			dup2(fds->fd[WRITE], STDOUT_FILENO);
			close(fds->fd[WRITE]);
		}
	}
}
