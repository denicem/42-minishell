/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/26 14:29:18 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	create_prcs(t_table *table, t_exec *fds);
static void	end_prcs(t_exec *fds);

void	exec_loop(t_table *table)
{
	t_table	*tmp;
	t_exec	*fds;

	tmp = table;
	fds = new_exec();
	while (tmp)
	{
		if (tmp->log_op != COMMAND)
			tmp = tmp->next;
		if (tmp->prev == NULL && tmp->next == NULL
			&& !tmp->redir && check_builtin(tmp))
		{
			g_exit_status = built_in_exec(tmp);
			fds->i++;
			break ;
		}
		else
			fds->pid = create_prcs(tmp, fds);
		fds->i++;
		tmp = tmp->next;
	}
	end_prcs(fds);
}

static int	create_prcs(t_table *table, t_exec *fds)
{
	pipe(fds->fd);
	define_sig_prc(table);
	fds->pid = fork();
	if (fds->pid == 0)
	{
		close(fds->fd[READ]);
		if (!table->prev && !table->next
			&& !table->redir && !check_builtin(table))
			g_exit_status = exec(table);
		else
		{
			route_stdin(table, fds);
			route_stdout(table, fds);
			g_exit_status = exec(table);
		}
	}
	close(fds->tmp_fd);
	close(fds->fd[WRITE]);
	dup2(fds->fd[READ], fds->tmp_fd);
	close(fds->fd[READ]);
	return (fds->pid);
}

static void	end_prcs(t_exec *fds)
{
	close(fds->stin);
	close(fds->stout);
	close(fds->tmp_fd);
	while (fds->i > 0)
	{
		waitpid(0, &fds->pid, 0);
		if (WIFEXITED(fds->pid))
			g_exit_status = WEXITSTATUS(fds->pid);
		fds->i--;
	}
}

int	exec(t_table *table)
{
	char	**env_arr;

	env_arr = get_env_arr();
	if (!env_arr)
		perror("Could not resolve environ array.\n");
	if (built_in_exec(table))
	{
		if (execve(table->cmd_arr[0], table->cmd_arr, env_arr) == -1)
			g_exit_status = -1;
	}
	return (g_exit_status);
}
