#ifndef FILLIT_H
# define FILLIT_H

# define BUFF_SIZE 21
# define FIG_MAX 26

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>


typedef struct  s_t
{
    unsigned long    value;
    int         width;
    int         height;
    int     	x;
    int     	y;
    char		letter;
    struct s_t	*previous;
}				t_t;

unsigned long   get_tetfig(const char *buf);
int             validation(t_t *tet, unsigned long fig, char letter);
int             ft_read_inputfile(t_t *tet, int fd);

#endif