/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 13:09:40 by bpole             #+#    #+#             */
/*   Updated: 2019/10/20 12:23:44 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static long		get_tetfig(const char *buf)
{
	long		fig;
	int			i;

	fig = 0;
	i = 0;
	while (i < BUFF_SIZE - 1)
	{
		if (buf[i] == '#')
			fig |= 1LU << (i + i / 5 * 11);
		else if (buf[i] != '.' && buf[i] != '\n')
			return (0);
		else if (buf[i] == '\n' && ((i + 1) % 5 != 0))
			return (0);
		++i;
	}
	if (buf[i] && (buf[i] != '\0' && buf[i] != '\n'))
		return (0);
	return (fig);
}

static int		validation(t_tet *tet, long fig, char letter)
{
	static long	std[19] = {0x12C0142, 0x605, 0x64006400640072, 0x12C0278,
		0x258014C, 0xC8012C007B, 0x64012C00DF, 0xC802DC,
		0x2BC00E8, 0x64012C007B, 0xC8012C00DF, 0x12C0064007B,
		0x12C00C800DF, 0x6400640143, 0xC800C80143, 0x2BC0084,
		0x6402DC, 0x2BC01B0, 0x19002DC};
	int			i;

	i = 0;
	while (i < 19)
	{
		if (fig == std[i] / 100)
		{
			tet->value = std[i] / 100;
			tet->width = std[i] / 10 % 10;
			tet->height = std[i] % 10;
			tet->letter = letter;
			return (0);
		}
		i++;
	}
	return (-1);
}

int				read_file(t_tet *tet, int fd, int count)
{
	char		buf[BUFF_SIZE];
	long		fig;
	char		letter;
	int			bates;
	int			tmp;

	letter = 'A';
	while ((bates = read(fd, buf, 21)) >= 20)
	{
		tmp = bates;
		if (!(fig = get_tetfig(buf)))
			return (-1);
		while (!(fig & 0xf))
			fig >>= 16;
		while (!(fig & 0x1000100010001))
			fig >>= 1;
		if (letter > 'Z' || validation(tet++, fig, letter++))
			return (-1);
		count++;
	}
	return (bates == 0 && tmp == 20 ? count : -1);
}

int				find_solution(t_tet *tet, short *arr, int size)
{
	if (!tet->value)
		return (1);
	if (tet->previous)
	{
		tet->x = tet->previous->x + 1;
		tet->y = tet->previous->y;
	}
	else
	{
		tet->x = 0;
		tet->y = 0;
	}
	while (tet->y + tet->height <= size)
	{
		while (tet->x + tet->width <= size)
		{
			if (!(*(long *)(arr + tet->y) & tet->value << tet->x))
			{
				(*(long *)(arr + tet->y) |= tet->value << tet->x);
				if (find_solution(tet + 1, arr, size))
					return (1);
				(*(long *)(arr + tet->y) ^= tet->value << tet->x);
			}
			tet->x++;
		}
		tet->x = 0;
		tet->y++;
	}
	return (0);
}

void			print_result(t_tet *tet, int size)
{
	char		*str;
	int			i;

	ft_memset(str = ft_strnew(size * size), '.', size * size);
	while ((i = 0) == 0 && tet->letter)
	{
		while (i < 64)
		{
			if ((1UL << i) & tet->value)
				str[i % 16 + (i / 16 + tet->y) * size + tet->x] = tet->letter;
			i++;
		}
		tet++;
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		if (++i % size == 0)
			ft_putchar('\n');
	}
	free(str);
}
