/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:53:02 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/12 22:14:51 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_stringbuilder	*sb_create(void)
{
	t_stringbuilder	*sb;

	sb = calloc(1, sizeof(t_stringbuilder));
	if (!sb)
		return (NULL);
	sb->str = ft_calloc(1, sizeof(char));
	sb->len = 0;
	return (sb);
}

int	sb_destroy(t_stringbuilder *sb)
{
	free(sb->str);
	sb->str = NULL;
	sb->len = 0;
	free(sb);
	sb = NULL;
	return (0);
}

int	sb_clear(t_stringbuilder *sb)
{
	free(sb->str);
	sb->str = ft_calloc(1, sizeof(char));
	if (!sb->str)
	{
		free(sb);
		return (2);
	}
	sb->len = 0;
	return (0);
}

void	sb_copy_oldstr(t_stringbuilder *sb, char **newstr)
{
	int	i;

	i = 0;
	while (sb->str[i] && i < sb->len)
	{
		(*newstr)[i] = sb->str[i];
		i++;
	}
}
