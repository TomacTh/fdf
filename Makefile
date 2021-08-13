CC		=	gcc
NAME	=	fdf
NAME_BONUS =	fdf_bonus
CFLAGS	= 	-Wall -Wextra  -ggdb
LDFLAGS =	-lmlx -framework OpenGL -framework AppKit
INCLUDES		=	./include
SRCS = $(addprefix ./srcs/, ft_fdf.c ft_atoi_base.c ft_coord_and_utils.c ft_get_next_line.c ft_init.c ft_max_min.c ft_parse.c ft_split.c ft_utils.c ft_utils2.c ft_utils3.c ft_utils4.c )
SRCSBONUS=  $(addprefix ./srcs_bonus/, ft_fdf_bonus.c ft_atoi_base_bonus.c ft_coord_and_utils_bonus.c ft_get_next_line_bonus.c ft_init_bonus.c ft_max_min_bonus.c ft_parse_bonus.c ft_split_bonus.c ft_utils_bonus.c ft_utils2_bonus.c ft_utils3_bonus.c ft_utils4_bonus.c ft_adjust_bonus.c ft_keys_bonus.c)

OBJS	=	$(SRCS:.c=.o)
OBJSBONUS =	$(SRCSBONUS:.c=.o)

all:	$(NAME)

bonus: $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(NAME_BONUS):	$(OBJSBONUS) 
	$(CC) $(CFLAGS) $(OBJSBONUS) $(LDFLAGS) -o $(NAME_BONUS)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJSBONUS)

fclean:	clean
	rm -f $(NAME) $(NAME_BONUS)


re:	fclean all

.PHONY:	all bonus clean re install
