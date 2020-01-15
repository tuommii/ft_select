/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:39:46 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 11:54:20 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	check_arrow_keys(int code, t_list *list, t_terminal *term)
{
	if (!list || !term)
		return (0);
	if (code == LEFT)
		move_left(term);
	else if (code == RIGHT)
		move_right(term);
	else if (code == UP)
		move_up(term);
	else if (code == DOWN)
		move_down(term);
	if (code == UP || code == RIGHT || code == DOWN || code == LEFT)
		return (PRESSED_KEY);
	return (0);
}

static int	check_other_keys(int code, t_list **list, t_terminal *term)
{
	if (code == SPACE)
	{
		toggle_selected(term, *list, term->i);
		if (term->i < term->count)
			move_right(term);
		return (1);
	}
	if (code == BACKSPACE || code == DELETE)
	{
		ft_lstdelat(list, term->i, (void *)delete_arg);
		if (term->count > 0)
			term->count--;
		if (term->count == 0)
		{
			config_terminal(1);
			cleanup(list);
			exit(0);
		}
		if (term->i == term->count)
			term->i--;
		return (1);
	}
	return (0);
}

static int	key_pressed(int code, t_list **list, t_terminal *term)
{
	if (check_arrow_keys(code, *list, term))
	{
		set_underlined(*list, term->i);
		return (PRESSED_KEY);
	}
	else if (check_other_keys(code, list, term))
	{
		set_underlined(*list, term->i);
		return (PRESSED_KEY);
	}
	else if (code == ENTER)
		return (PRESSED_ENTER);
	else if (code == ESC)
		return (PRESSED_ESC);
	return (0);
}

int			keyboard(t_list **list, t_terminal *term)
{
	char	seq[KEYBOARD_BUFF_LEN + 1];
	int		i;
	int		code;

	ft_bzero(seq, KEYBOARD_BUFF_LEN);
	read(STDIN_FILENO, &seq, KEYBOARD_BUFF_LEN);
	seq[KEYBOARD_BUFF_LEN] = '\0';
	i = 0;
	code = 0;
	while (seq[i])
	{
		code += seq[i];
		i++;
	}
	term->code = code;
	return (key_pressed(code, list, term));
}
