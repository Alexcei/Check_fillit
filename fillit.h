/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 13:09:13 by bpole             #+#    #+#             */
/*   Updated: 2019/10/20 12:24:45 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define BUFF_SIZE 21
# define FIG_MAX 26

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct		s_tet
{
	long			value;
	char			letter;
	int				width;
	int				height;
	int				x;
	int				y;
	struct s_tet	*previous;
}					t_tet;

int				    read_file(t_tet *tet, int fd, int size);
int				    find_solution(t_tet *tet, short *arr, int size);
void			    print_result(t_tet *tet, int size);

#endif
