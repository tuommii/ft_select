/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:59:39 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/21 20:08:28 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_info(t_list *list, t_terminal *term)
{
	if (term->height < term->rows_needed)
	{
		tputs(CL, 1, print_char);
		ft_dprintf(OUTPUT, "No enough space to show options!\n");
	}
	else
	{
		traverse_args(list, term, print_arg);
	}
}

void	print_arg(t_list *node, t_terminal *term)
{
	t_arg	*arg;
	int		delta;
	int		len;

	if (!node->content)
		return ;
	arg = (t_arg *)node->content;
	if (!arg || !arg->text)
		return ;
	len = 0;
	len = ft_strlen(arg->text);
	delta = term->max_len - len;
	if (arg->underlined)
		tputs(US, 1, print_char);
	if (arg->selected)
		tputs(SO, 1, print_char);
	ft_dprintf(OUTPUT, "%s", arg->text);
	if (arg->selected)
		tputs(SE, 1, print_char);
	if (arg->underlined)
		tputs(UE, 1, print_char);
	while (delta-- > 0)
		ft_dprintf(2, " ");
}

void	print_results(int code, t_list *list, t_terminal term)
{
	int		counter;
	t_arg	*arg;

	if (!code)
		return ;
	counter = 0;
	arg = NULL;
	while (list != NULL)
	{
		arg = (t_arg *)list->content;
		if (arg->selected)
		{
			ft_dprintf(STDOUT_FILENO, "%s", arg->text);
			counter++;
			if (counter < term.selected_count)
				ft_dprintf(STDOUT_FILENO, " ");
		}
		list = list->next;
	}
	if (counter)
		ft_dprintf(STDOUT_FILENO, "\n");
}

int		print_char(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}
