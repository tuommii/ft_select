/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 19:51:17 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 12:51:52 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/libft.h"
# include <sys/ioctl.h>
# include <stdlib.h>
# include <signal.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

/*
** Highlight
*/

# define SO (tgetstr("so", NULL))
# define SE (tgetstr("se", NULL))

/*
** Underline
*/

# define US (tgetstr("us", NULL))
# define UE (tgetstr("ue", NULL))

/*
** Clear
*/

# define CL (tgetstr("cl", NULL))

# define KEYBOARD_BUFF_LEN 4

# define OUTPUT STDERR_FILENO

# define ESC 27
# define LEFT 186
# define UP 183
# define RIGHT 185
# define DOWN 184
# define SPACE 32
# define ENTER 10
# define BACKSPACE 127
# define DELETE 295

# define PRESSED_KEY 1
# define PRESSED_ENTER -2
# define PRESSED_ESC -1

# ifndef TIOCGSIZE
#  define TIOCGSIZE TIOCGWINSZ
# endif

typedef struct		s_arg
{
	char			*text;
	int				selected;
	int				underlined;
}					t_arg;

typedef struct		s_terminal
{
	struct termios	config;
	struct termios	backup;
	char			*name;
	int				height;
	int				width;
	int				row_total;
	int				rows_needed;
	int				max_len;
	int				cols;
	int				code;
	int				i;
	int				count;
	int				selected_count;
}					t_terminal;

int					g_kill;

void				check_terminal_config(void);
void				config_terminal(int reset);
void				init_struct(t_terminal *term, int max_len, int argc);

void				get_term_size(t_terminal *term);
void				cleanup(t_list **list);
void				toggle_selected(t_terminal *term, t_list *lst, int index);
void				set_underlined(t_list *lst, int index);

int					keyboard(t_list **list, t_terminal *term);

int					args_to_list(t_list **list, char **argv, int argc);
void				traverse_args(t_list *lst, t_terminal *term, \
					void(*f)(t_list *elem, t_terminal *term));
void				delete_arg(t_arg *arg);

void				print_data(t_list *list, t_terminal *term);
void				print_row(t_list *node, t_terminal *term);
void				print_selected(int code, t_list *list, t_terminal term);
int					print_char(int c);

void				move_left(t_terminal *term);
void				move_right(t_terminal *term);
void				move_up(t_terminal *term);
void				move_down(t_terminal *term);

void				listen_signals(void);
void				signal_handler(int sig);
void				watch_kill(t_list **list);

#endif
