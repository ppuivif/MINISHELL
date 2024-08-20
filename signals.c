/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:04 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 14:57:22 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_c(int sign)
{
	g_sign = sign;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ctrl_c2(int sign)
{
	g_sign = sign;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

static void	ctrl_backslash(int sign)
{
	g_sign = sign;
	ft_putstr_fd("Quit\n", 1);
	(void)sign;//see if void necessary
}

void	signals(int sign)
{
	if (sign == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrl_c);//CTRL C dans readline
	}
	else
	{
		signal(SIGQUIT, ctrl_backslash);
		signal(SIGINT, ctrl_c2);//CTRL C apres readline
	}
}

// see IOCTL for heredoc with EOF
