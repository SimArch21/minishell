/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/31 19:49:54 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we want to count the lines of the array
int	lines_counter(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

//we have to check if the flag of the echo cmd is written in that way :
//-nnnnnnnnnnnnn -> that is also considered as correct
static int	check_flag(char *flag)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (flag[i])
	{
		if (flag[i] == '-' && i == 0)
		{
			i++;
			check = 1;
		}
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	if (check == 1 && i == (int)ft_strlen(flag))
		return (1);
	return (0);
}

//in this function there is the same verification as the previous one
//because the user can write: echo -n -n -nnnn -nn test
//and we have to return, without line break: test
static int	builtin_echo_flag_n(t_mini *mini, t_cmd *command, int i, int wc)
{
	char	*content;

	while (command->str[i])
	{
		while (command->str[i] && (ft_strcmp_simple(command->str[i], "-n") == 0
				|| check_flag(command->str[i]) == 1))
			i++;
		//printf("command->str[i] = _%s_\n", command->str[i]);
		content = final_expansion(mini, command->str[i]);
		if (!content)
			print_error(mini, 2);
		if (write(1, content, ft_strlen(content)) == -1)
			print_error(mini, 0);//keycode = write has failed
		if (i < wc - 1)
			if (write(1, " ", 1) == -1)
				return (print_error(mini, 0), 0);//keycode = write has failed
		i++;
		free(content);
	}
	return (1);
}

//in this function, the argument *command is type: mini->cmd
//(we could only work with 1 argument)
//for example: echo hello     world     $PWD
//index are  :   0    1         2         3
//the result : hello world /path/
int	builtin_echo(t_mini *mini, t_cmd *command)
{
	int		wordcount;
	int		i;
	char	*content;

	wordcount = lines_counter(command->str);
	printf("wordcount = %i\n", wordcount);
	i = 1;
	if (command->str[i] && (ft_strcmp_simple(command->str[i], "-n") == 0
			|| check_flag(command->str[i]) == 1))//if we have the flag -n
		return (builtin_echo_flag_n(mini, command, 2, wordcount));
	//else if (command->str[i] && (ft_strcmp(command->str[i], "$?") == 0))
		//printf("%i\n", mini->exit_code);
	else//if there is no flag and only the echo cmd
	{
		while (command->str[i])
		{
			//printf("command->str[i] = _%s_\n", command->str[i]);
			content = final_expansion(mini, command->str[i]);
			if (!content)
				print_error(mini, 2);
			if (write(1, content, ft_strlen(content)) == -1)
				print_error(mini, 0);//keycode = write has failed
			if (i < wordcount - 1)
				if (write(1, " ", 1) == -1)
					return (print_error(mini, 0), 0);//keycode = write has failed
			i++;
			free(content);
		}
		if (write(1, "\n", 1) == -1)
			return (print_error(mini, 0), 0);//keycode = write has failed
	}
	return (1);
}