/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:47:43 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 15:57:21 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pre_executor(t_mini *mini)
{
	signal(SIGQUIT, sigquit_handler);
	mini->inside_cmd = 1;
	g_status = 0;
	count_pipes(mini);
	if (mini->pipes == 0)
		handle_single_cmd(mini, mini->cmd);
	else
		executor(mini);
	if (g_status != 0)
		mini->error_code = g_status + 128;
	mini->inside_cmd = 0;
	return (EXIT_SUCCESS);
}
// Generador de números pseudoaleatorios lineal congruencial (LCG)
// LCG: valores típicos para un generador simple

static int	generate_random_number(void)
{
	static unsigned int	seed = 12345;

	seed = (seed * 1103515245 + 12345) & 0x7fffffff;
	return (seed % 10000);
}

char	*generate_filename(void)
{
	char		*str;
	char		*num;

	num = ft_itoa(generate_random_number());
	str = ft_strjoin("hdoc_tmp_file", num);
	free(num);
	return (str);
}

void	remove_eof_quotes(t_lexer *node)
{
	char	*str;

	str = ft_strdup(node->str);
	free(node->str);
	if (str && (str[0] == '\"' || str[0] == '\''))
		node->str = ft_substr(str, 1, ft_strlen(str) - 2);
	free(str);
}

t_env_lst	*find_node_path(t_env_lst *lst_env)
{
	t_env_lst	*tmp;

	tmp = lst_env;
	while (tmp)
	{
		if (ft_strcmp(lst_env->key, "PATH") == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
