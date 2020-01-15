/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:07:28 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 11:53:37 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	get_term_size(t_terminal *term)
{
	struct winsize w;

	ioctl(OUTPUT, TIOCGSIZE, &w);
	term->height = w.ws_row;
	term->width = w.ws_col;
	term->cols = term->width / term->max_len;
	if (term->cols == 0 || term->cols == 1)
	{
		term->rows_needed = term->count;
	}
	else
	{
		term->rows_needed = term->count / term->cols;
		if ((term->count % term->cols))
			term->rows_needed++;
	}
}

void	set_underlined(t_list *lst, int index)
{
	int		i;
	t_arg	*arg;

	i = 0;
	while (lst != NULL)
	{
		arg = (t_arg *)lst->content;
		if (i == index)
		{
			arg->underlined = 1;
		}
		else
			arg->underlined = 0;
		lst = lst->next;
		i += 1;
	}
}

void	toggle_selected(t_terminal *term, t_list *lst, int index)
{
	int		i;
	t_arg	*arg;

	if (!lst)
		return ;
	i = 0;
	while (lst != NULL)
	{
		arg = (t_arg *)lst->content;
		if (i == index)
		{
			if (arg->selected)
			{
				arg->selected = 0;
				term->selected_count--;
			}
			else
			{
				arg->selected = 1;
				term->selected_count++;
			}
		}
		lst = lst->next;
		i += 1;
	}
}

void	cleanup(t_list **list)
{
	t_list *temp;

	while (*list != NULL)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->content);
		free(temp);
	}
}

int		print_char(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}
