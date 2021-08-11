#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

# define BUFFER_SIZE 4096

typedef struct s_gnl
{
	char	*buf;
	size_t	i;
	size_t	max;
	int		y;
}			t_gnl;

typedef struct s_img {
	void	*img;
	int		*addr;
	int		bpp;
	int		line;
	int		w;
	int		h;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void	*ptr;
	void	*win_ptr;
	t_img	img;
}				t_mlx;

typedef	struct	s_point
{
	unsigned int	z;
	int				color;
}					t_point;

typedef struct	s_coordinates
{
	float x;
	float y;
	float x1;
	float y1;
}				t_coordinates;


typedef struct s_fdf
{
	t_mlx			*mlx;
	t_point			**map;
	unsigned int	width;
	unsigned int	height;
	int				fd;
	int				error_code;
}					t_fdf;


void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		get_next_line(int fd, char **line);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
int		protect_malloc(void **ptr, size_t lenght);
char	**free_split(char **strs, int len);
int		ft_atoi_base(char *str, char *base);
int		recursive_parse(t_fdf *fdf, unsigned int len);
unsigned int	tab_len(void **tab);
int		recursive_error(char *str, char **strs, unsigned int len, t_fdf *fdf);
char	*ft_strndup(const char *s, size_t size);
char	*ft_str_tolower(char *str);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
