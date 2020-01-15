/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:58:51 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 12:24:24 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		args_to_list(t_list **list, char **argv, int argc)
{
	int		i;
	int		max;
	int		len;
	t_arg	arg;
	t_list	*temp;

	i = argc - 1;
	max = 0;
	arg.selected = 0;
	arg.underlined = 0;
	while (i >= 1)
	{
		len = ft_strlen(argv[i]);
		if (len > max)
			max = len;
		arg.text = argv[i];
		temp = ft_lstnew(&arg, sizeof(t_arg));
		ft_lstadd(list, temp);
		i--;
	}
	return (max);
}

void	delete_arg(t_arg *arg)
{
	arg->text = NULL;
}

void	traverse_args(t_list *lst, t_terminal *term,\
		void (*f)(t_list *elem, t_terminal *term))
{
	static int	started = 0;
	int			i;

	if (!lst || !f)
		return ;
	i = 1;
	if (!started && term->count > 0)
	{
		set_underlined(lst, term->i);
	}
	started = 1;
	while (lst != NULL)
	{
		if (i * term->max_len > term->width)
		{
			ft_printf("\n");
			i = 1;
		}
		f(lst, term);
		i++;
		lst = lst->next;
	}
}
