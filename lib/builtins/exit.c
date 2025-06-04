/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:31:18 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 16:14:29 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

void	overflow_happen(char *args, int checker)
{
	if (checker == 1)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args, 2);
		ft_putendl_fd(": numeric argument required", 2);
		gc_clear();
		exit(2);
	}
	return ;
}

void	check_valid_arg(char *arg, int *is_numeric)
{
	int		i;
	int		checker;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && (arg[i] == '-' || arg[i] == '+'))
			i++;
		if (!ft_isdigit(arg[i]))
		{
			*is_numeric = 0;
			break ;
		}
		i++;
	}
	checker = check_overflow(arg);
	overflow_happen(arg, checker);
	return ;
}

void	if_not_numeric(char *args, int is_numeric)
{
	if (!is_numeric)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args, 2);
		ft_putendl_fd(": numeric argument required", 2);
		gc_clear();
		exit(2);
	}
	return ;
}

void	exit_fun(t_command *cmd)
{
	char	**args;
	int		is_numeric;
	long	status;

	args = (char **)cmd->args->array;
	is_numeric = 1;
	if (g_minishell.parser->pipeline->cmd_count == 1)
		ft_putendl_fd("exit", 2);
	if (args[1] == NULL)
	{
		gc_clear();
		exit(g_minishell.exit_code);
	}
	check_valid_arg(args[1], &is_numeric);
	if_not_numeric(args[1], is_numeric);
	if (args[2] != NULL)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		g_minishell.exit_code = 1;
		return ;
	}
	status = ft_atoi(args[1]) % 256;
	gc_clear();
	exit((unsigned char)status);
}
