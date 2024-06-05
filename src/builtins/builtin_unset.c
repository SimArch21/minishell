/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:25:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/14 13:04:40 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//**head refers to the env builtin list
//the str refers to the unset_arg to remove (for example PWD)
//this function is basically remove a node

int	scan_start_unset_arg(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->str[1] || cmd->str[1][0] == '_'
		|| (cmd->str[1][0] == '\'' && cmd->str[1][1] == '\0'))
		return (EXIT_SUCCESS);
	while (cmd->str[1][i])
		i++;
	i--;
	if (cmd->str[1][i] == '/' || cmd->str[1][i] == '\\')
	{
		ft_putstr_fd("shelldone: unset: `", STDERR_FILENO);
		ft_putstr_fd(&cmd->str[1][i], STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

int	detect_unset_error(t_cmd *cmd)
{
	char	*unset_arg;
	int		i;

	i = 0;
	unset_arg = cmd->str[1];
	if (is_equal(&unset_arg[0]) != 0)
	{
		ft_putendl_fd("shelldone: unset: not a valid identifier",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (unset_arg[i++])
	{
		if (unset_arg[i++] == '/')
		{
			ft_putstr_fd("shelldone: unset: `", STDERR_FILENO);
			ft_putstr_fd(&unset_arg[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}


// hacer que si el index es <1000 no se elimine, pero de el success, porque? porque asi no tendremos errores o segs
// que eliminen una env del sistema como home
int	builtin_unset(t_mini *mini, t_builtin **head, t_cmd *cmd)
{
	int			i;
	t_builtin	*current;
	t_builtin	*previous;

	i = 0;
	while (cmd->str[++i])
	{
		if (scan_start_unset_arg(cmd) == 0)
			return (EXIT_SUCCESS);
		if (detect_unset_error(cmd) == 1)
			return (EXIT_FAILURE);
		previous = NULL;
		current = *head;
		while (current)
		{
			if (ft_strlen(current->key) == ft_strlen(cmd->str[i]) &&
				ft_strcmp_simple(current->key, cmd->str[i]) == 0)
			{
				if (previous == NULL)
					*head = current->next;
				else
					previous->next = current->next;
				free(current->key);
				free(current->value);
				free(current);
				break ;
			}
			previous = current;
			current = current->next;
		}
	}
	if (mini)
		printf("");
	// buioint pwd actualizar lista nodos env verficiar si hay pwd y si no cogerlo del getcurrent directory y actualizar el nodo;
	ft_free_double_array(mini->env_cpy);
	concat_lst_env(mini);
	return (EXIT_SUCCESS);
}