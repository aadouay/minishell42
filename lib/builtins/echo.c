/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 23:39:09 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:13:36 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_new_line(char **arg, int *new_line, int *i)
{
	int	j;

	while (arg[*i] && arg[(*i)][0] == '-' && arg[*i][1] == 'n')
	{
		j = 2;
		while (arg[*i][j] == 'n')
			j++;
		if (arg[*i][j] == '\0')
			*new_line = 0;
		else
			break ;
		(*i)++;
	}
}

void	echo(t_command *cmd)
{
	int		i;
	int		new_line;
	char	*arg;

	i = 1;
	new_line = 1;
	check_new_line((char **)cmd->args->array, &new_line, &i);
	while (i < cmd->args_count)
	{
		arg = *(char **)get_element(cmd->args, i);
		if (write(1, arg, ft_strlen(arg)) == -1)
		{
			ft_putendl_fd("echo: write error: No space left on device", 2);
			g_minishell.exit_code = 1;
			return ;
		}
		if (i + 1 < cmd->args_count)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_line == 1)
		printf("\n");
	g_minishell.exit_code = 0;
	return ;
}
