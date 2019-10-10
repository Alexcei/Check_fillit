#include <stdio.h>
#include "fillit.h"

void    print_fig(unsigned long value)
{
    int i = 0;
    while (i++ < 64) {
        printf("%d", (value & 1 ? 1 : 0));
        value >>= 1;
        if (!(i % 16))
            printf("\n");
    }
    printf("\n");
}

void    print_tet(t_t *tet)
{
    while (tet->letter)
    {
        printf("%c %d %d %d\n", tet->letter, tet->x, tet->y, tet->flag);
        //print_fig(tet->value);
        tet++;
    }
}

int     solver(t_t *tet, unsigned long map, int size, int x, int y)
{
    t_t             *cpy_tet;
    unsigned long   tmp;

    cpy_tet = tet;
    while (cpy_tet->letter)
    {
        if (!cpy_tet->flag)
        {
            if (x + cpy_tet->width > size)
            {
                x = 0;
                y++;
                map >>= 16;
            }
            if (y + cpy_tet->height > size)
                return (0);
            if (!(map & cpy_tet->value << x))
            {
                tmp = map;
                map |= cpy_tet->value << x;
                cpy_tet->flag = 1;
                cpy_tet->x = x;
                cpy_tet->y = y;
                print_fig(map);
                if (solver(tet, map, size, x, y))
                    return (1);
                map = tmp;
                cpy_tet->flag = 0;
                cpy_tet->x = 0;
                cpy_tet->y = 0;
                cpy_tet++;
                continue;
            }
            x++;
        }
        else
            cpy_tet++;
    }
    return (1);
}

void    print_result(t_t *tet, int size)
{
    unsigned long   mask;
    char    *str;
    int     i;

    mask = 1UL;
    str = ft_strnew(size * size);
    ft_memset(str, '.', size * size);
    while (tet->letter)
    {
        i = 0;
        while (i < 64)
        {
            if ((mask << i) & tet->value)
                str[i % 16  + i / 16 * (size) + tet->x + tet->y * size] = tet->letter;
            i++;
        }
        tet++;
    }
    i = 0;
    while (*str && ++i)
    {
        ft_putchar(*str++);
        if (i % size == 0)
            ft_putchar('\n');
    }
    ft_putchar('\n');
}

int     main(void)
{
    unsigned long   map;
    int             size;
    t_t		*tet;
    int		fd;
    int             x;
    int             y;

    if (2 != 2)
        return (ft_put_error("usage : ./fillit input_tetraminos"));
    fd = open("test", O_RDONLY);
    tet = (t_t *)malloc(sizeof(t_t) * FIG_MAX + 1);
    if (fd == -1 || !tet)
        return (ft_put_error("error"));
    ft_bzero(tet, sizeof(t_t) * FIG_MAX + 1);
    if (ft_read_inputfile(tet, fd))
        return (ft_put_error("error"));

    x = 0;
    y = 0;
    map = 0UL;
    size = 7;
    solver(tet, map, size, x, y);
    print_tet(tet);

    print_result(tet, size);
    return (0);
}
