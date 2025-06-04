/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:01:36 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 17:25:29 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args(t_command *cmd)
{
	if (cmd->args_count > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		g_minishell.exit_code = 1;
		return (1);
	}
	return (0);
}

void	change_pwd_and_old(char *new, char *old)
{
	ch_in_env("OLDPWD", old);
	ch_in_env("PWD", new);
	free(new);
	free(old);
}

int	check_getcwd(char *new_pwd)
{
	if (!new_pwd)
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory", \
			2);
		g_minishell.exit_code = 0;
		return (1);
	}
	return (0);
}

int	we_have_only_cd(t_command *cmd)
{
	if (cmd->args_count == 1)
	{
		ft_putendl_fd("cd: missing path argument", 2);
		g_minishell.exit_code = 1;
		return (1);
	}
	return (0);
}

void	cd(t_command *cmd)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (check_args(cmd))
		return ;
	if (we_have_only_cd(cmd))
		return ;
	path = *(char **)get_element(cmd->args, 1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		ft_putendl_fd("cd: No such file or directory", 2);
		g_minishell.exit_code = 1;
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	if (check_getcwd(new_pwd))
		return ;
	change_pwd_and_old(new_pwd, old_pwd);
	g_minishell.exit_code = 0;
	return ;
}
