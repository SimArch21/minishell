/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/06 18:18:22 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_expander(t_mini *mini, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	tmp->str = expand_cmd_line(mini, tmp->str);
	while (tmp->redirections)
	{
		if (tmp->redirections->token != HDOC)
			tmp->redirections->str = expand_str_line(mini,
					tmp->redirections->str);
		tmp->redirections = tmp->redirections->next;
	}
}

// contains char** cmd line ==> [[cat] [hola.c]] [[echo] [$VARIABLE]]
// expand cmd line. only cmd flags and args of the cmd
char	**expand_cmd_line(t_mini *mini, char **str)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	while (str[i])
	{
		new = final_expansion(mini, str[i]);
		printf("NEW_cmd_line : _%s_\n", new);
		free(str[i]);
		str[i] = new;
		i++;
	}
	return (str);
}

// expand str==> filename
char	*expand_str_line(t_mini *mini, char *str)
{
	char	*new;

	new = NULL;
	new = final_expansion(mini, str);
	printf("NEW_str_line : _%s_\n", new);
	free(str);
	str = new;
	return (str);
}
