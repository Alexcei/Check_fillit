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
        printf("%c %d %d\n", tet->letter, tet->width, tet->height);
        print_fig(tet->value);
        tet++;
    }
}

int     solver(t_t *tet)
{
    unsigned long   map;
    int             size;
    int             x;
    int             y;

    x = 0;
    y = 0;
    map = 0UL;
    size = 16;
    while (tet->letter)
    {
        if (x == size)
        {
            x = 0;
            y++;
            map >>= 16;
        }
        if (!(map & tet->value << x))
        {
            map |= tet->value << x;
            tet++;
        }
        print_fig(map);
        x++;
    }
    return (map);
}

int     main(void)
{
    t_t		*tet;
    int		fd;

    if (2 != 2)
        return (ft_put_error("usage : ./fillit input_tetraminos"));
    fd = open("test", O_RDONLY);
    tet = (t_t *)malloc(sizeof(t_t) * FIG_MAX + 1);
    if (fd == -1 || !tet)
        return (ft_put_error("error"));
    ft_bzero(tet, sizeof(t_t) * FIG_MAX + 1);
    if (ft_read_inputfile(tet, fd))
        return (ft_put_error("error"));
    print_tet(tet);
    solver(tet);

    return (0);
}
