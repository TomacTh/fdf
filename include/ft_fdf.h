/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:25:06 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 17:11:44 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H
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
# define ESC_KEY 53

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

typedef struct s_mlx
{
	void	*ptr;
	void	*win_ptr;
	t_img	*img;
}				t_mlx;

typedef struct s_point
{
	int	z;
	int	color;
}			t_point;

typedef struct s_coordinates
{
	float	x;
	float	y;
	float	x1;
	float	y1;
}				t_coordinates;

typedef struct s_fdf
{
	t_mlx			*mlx;
	t_point			**map;
	unsigned int	width;
	unsigned int	height;
	int				fd;
	int				error_code;
	float			zoom;
	int				z_depth;
	int				shift_x;
	int				shift_y;
}						t_fdf;

void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_putstr_fd(char *s, int fd);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strdup(const char *s);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				get_next_line(int fd, char **line);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
int				protect_malloc(void **ptr, size_t lenght);
char			**free_split(char **strs, int len);
int				ft_atoi_base(char *str, char *base);
char			*ft_strndup(const char *s, size_t size);
char			*ft_str_tolower(char *str);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strjoin(char const *s1, char const *s2);

float			get_abs(float i);
float			get_fmax(float a, float b);
float			get_fmin(float a, float b);
int				get_imax(int a, int b);
int				get_imin(int a, int b);

void			quit(t_fdf *fdf, char *err);
int				check_file(char *filename);
int				check_arg(int ac, char *filename);
void			set_zoom_shift_and_z(t_fdf *fdf);
void			init_mlx(t_mlx *mlx, t_fdf *fdf);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			zoom_coord(t_coordinates *coord, float zoom);
void			shift_coord(t_coordinates *coord, int shift_x, int shift_y);
int				recursive_parse(t_fdf *fdf, unsigned int len);
unsigned int	tab_len(void **tab);
int				recursive_error(char *str, char **strs,
					unsigned int len, t_fdf *fdf);
void			iso(float *x, float *y, int z, int z_value);
void			calc_step_and_max(float *x_step, float *y_step,
					int *max, t_coordinates coord);
#endif
