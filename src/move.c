/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:36:47 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 12:21:30 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	move_left(t_terminal *term)
{
	if (term->i == 0)
		term->i = term->count - 1;
	else if (term->i > 0)
		term->i--;
}

void	move_right(t_terminal *term)
{
	if (term->i == term->count - 1)
		term->i = 0;
	else
		term->i++;
}

void	move_up(t_terminal *term)
{
	if (term->i < term->cols)
		term->i = term->count - 1;
	else
		term->i -= term->cols;
}

void	move_down(t_terminal *term)
{
	if (term->i > term->count - 1 - term->cols)
		term->i = 0;
	else
		term->i += term->cols;
}
