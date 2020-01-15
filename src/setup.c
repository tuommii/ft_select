/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 10:55:58 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 12:20:48 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	config_terminal(int reset)
{
	static struct termios backup;
	static struct termios new_config;

	if (reset)
	{
		tputs(tgetstr("te", NULL), 1, print_char);
		tputs(tgetstr("ve", NULL), 1, print_char);
		tcsetattr(OUTPUT, TCSANOW, &backup);
	}
	else
	{
		tcgetattr(OUTPUT, &backup);
		new_config = backup;
		new_config.c_lflag &= ~(ECHO | ICANON);
		new_config.c_cc[VMIN] = 1;
		new_config.c_cc[VTIME] = 0;
		tcsetattr(OUTPUT, TCSANOW, &new_config);
		tputs(tgetstr("ti", NULL), 1, print_char);
		tputs(tgetstr("vi", NULL), 1, print_char);
	}
}

void	check_terminal_config(void)
{
	char buffer[2048];
	char *name;

	if (!(name = getenv("TERM")))
	{
		ft_dprintf(OUTPUT, "No terminal name");
		exit(1);
	}
	if (!isatty(OUTPUT))
	{
		ft_dprintf(OUTPUT, "No terminal detected!\n");
		exit(1);
	}
	if (tgetent(buffer, name) != 1)
	{
		ft_dprintf(OUTPUT, "No database or No entry found\n");
		exit(1);
	}
}

void	init_struct(t_terminal *term, int max_len, int argc)
{
	term->max_len = max_len;
	term->height = 0;
	term->row_total = 0;
	term->rows_needed = 0;
	term->width = 0;
	term->count = argc - 1;
	term->i = 0;
	term->code = 0;
	term->cols = 0;
	term->selected_count = 0;
}
