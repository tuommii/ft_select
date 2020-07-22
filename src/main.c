/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 19:49:09 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/22 09:42:26 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	display_loop(t_list **list, t_terminal *term)
{
	int		pressed;

	while (1)
	{
		pressed = 0;
		listen_signals();
		watch_kill(list);
		tputs(tgetstr("cl", NULL), 1, print_char);
		get_term_size(term);
		print_info(*list, term);
		pressed = keyboard(list, term);
		if (pressed == PRESSED_KEY)
			continue ;
		else if (pressed == PRESSED_ESC)
			break ;
		else if (pressed == PRESSED_ENTER)
			return (1);
	}
	return (0);
}

static void	check_args_error(int argc)
{
	if (argc < 2)
	{
		ft_dprintf(2, "Usage: ft_select <param> ...\n");
		exit(1);
	}
}

int			main(int argc, char **argv)
{
	t_list		*list;
	t_terminal	term;
	int			code;

	g_kill = 0;
	check_args_error(argc);
	check_terminal_config();
	list = NULL;
	init_struct(&term, args_to_list(&list, argv, argc) + 1, argc);
	config_terminal(0);
	code = display_loop(&list, &term);
	config_terminal(1);
	print_results(code, list, term);
	cleanup(&list);
	exit(0);
}
