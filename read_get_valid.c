#include "fillit.h"

unsigned long   get_tetfig(const char *buf)
{
    int             count;
    unsigned long	fig;
    int			    i;

    count = 0;
    fig = 0;
    i = 0;
    while (i < BUFF_SIZE - 1)
    {
        if (buf[i] == '#' && ++count)
            fig |= 1LU << (i + i / 5 * 11);
        else if (buf[i] != '.' && buf[i] != '\n')
            return (0);
        else if (buf[i] == '\n' && ((i + 1) % 5 != 0))
            return (0);
        ++i;
    }
    if (buf[i] && (buf[i] != '\0' && buf[i] != '\n'))
        return (0);
    return (count == 4 ? fig : 0);
}

int    validation(t_t *tet, unsigned long fig, char letter)
{
    static unsigned long    std[19] = {0x12C0142, 0x605, 0x64006400640072, 0x12C0278,
                                       0x258014C, 0xC8012C007B, 0x64012C00DF, 0xC802DC,
                                       0x2BC00E8, 0x64012C007B, 0xC8012C00DF, 0x12C0064007B,
                                       0x12C00C800DF, 0x6400640143, 0xC800C80143, 0x2BC0084,
                                       0x6402DC, 0x2BC01B0, 0x19002DC};
    int                     i;

    i = 0;
    while (i < 19)
    {
        if (fig == std[i] / 100)
        {
            tet->value = std[i] / 100;
            tet->width = std[i] / 10 % 10;
            tet->height = std[i] % 10;
            tet->letter = letter;
            tet->flag = 0;
            return (0);
        }
        i++;
    }
    return (-1);
}

int     ft_read_inputfile(t_t *tet, int fd, int count)
{
    char            buf[BUFF_SIZE];
    unsigned long   fig;
    char            letter;
    int             bates;
    int             tmp;

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