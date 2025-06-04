/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:47:04 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:33:17 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_minishell.from_child == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_minishell.exit_code = 130;
	}
}

void	setup_parent_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static int	minishell_core(char *input)
{
	g_minishell.handle_extra_line = 0;
	g_minishell.resev_signal_in_herdoc = 0;
	g_minishell.is_closed = true;
	input = readline("minishell➜ ");
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	add_history(input);
	g_minishell.parser = parser(input);
	if (!g_minishell.resev_signal_in_herdoc)
	{
		if (g_minishell.parser && g_minishell.is_closed)
			executor(g_minishell.parser->pipeline);
	}
	free(input);
	return (0);
}

int	main(int argc, const char **argv, char **envp)
{
	char	*input;

	(void)argv;
	if (argc > 1)
		return (EXIT_FAILURE);
	input = NULL;
	g_minishell.env = create_list_env(envp);
	g_minishell.exit_code = 0;
	rl_bind_key('\t', rl_complete);
	using_history();
	setup_parent_signals();
	while (1)
	{
		if (minishell_core(input))
			break ;
	}
	gc_clear();
	return (g_minishell.exit_code);
}
