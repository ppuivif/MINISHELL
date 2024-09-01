/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:04 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/01 14:49:31 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	ctrl_c(int sign)
{
	g_sign = sign;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);//remplace le contenu du buffer
	rl_redisplay();//affiche le contenu courant du buffer 
}

/*void ft_exit_heredoc(t_exec_struct *data)
{
	static t_exec_struct *save;

	save = NULL;
	if (!data)
	{
		if (save)
			free(save);
		return ;
	}
	save = data;
}

static void	ctrl_c2(int sign)
{
	ft_exit_heredoc(NULL);
	exit(130);
}*/


/*static void	ctrl_c2(int sign)
{
	g_sign = sign;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}*/

//void    here_doc(int sign)//solution Theau
static void	ctrl_c2(int sign)
{
//  char    c;

    g_sign = sign;
    rl_on_new_line();
    rl_replace_line("", 0);
    ioctl(0, TIOCSTI, "\n");
    (void)sign;
}

/*static void	ctrl_d2(sign)
{
    g_sign = sign;
	ft_putstr_fd("warning: here-document delimited by end-of-file\n", 1);
//	signal(SIGQUIT, SIG_IGN);
}*/

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
//		signal(SIGQUIT, ctrl_d2);//do not work
		signal(SIGQUIT, ctrl_backslash);
		signal(SIGINT, ctrl_c2);//CTRL C apres readline
	}
}

// see IOCTL for heredoc with EOF
