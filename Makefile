HEADER			=	includes/philo.h

NAME			=	philo

MAIN			=	main.c

SRCS			=	srcs/ft_strncmp.c\
					srcs/ft_isint.c\
					srcs/ft_atoi.c\
					srcs/ft_atoi_ull.c\
					srcs/ft_calloc.c\
					srcs/ft_free.c\
					srcs/ft_get_timestamp.c\
					srcs/ft_usleep.c\
					srcs/ft_is_fork_surrounded.c\
					srcs/ft_meals_count_reached.c\
					srcs/ft_start_eating.c\
					srcs/ft_start_sleeping.c\
					srcs/ft_return_error.c

OBJS			=	$(SRCS:.c=.o)\
					$(MAIN:.c=.o)

# HEADER_BONUS	=	includes/philo_bonus.h

# NAME_BONUS		=	philo_bonus

# MAIN_BONUS		=	main_bonus.c

# SRCS_BONUS		=	srcs/ft_strncmp.c\
# 					srcs/ft_isint.c\
# 					srcs/ft_atoi.c\
# 					srcs/ft_atoi_ull.c\
# 					srcs/ft_calloc.c\
# 					srcs/ft_free.c\
# 					srcs/ft_get_timestamp.c\
#					srcs/ft_usleep.c\
# 					srcs/ft_is_fork_surrounded.c\
# 					srcs/ft_meals_count_reached.c\
# 					srcs/ft_start_eating.c\
# 					srcs/ft_start_sleeping.c\
# 					srcs/ft_return_error.c

# OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)\
# 					$(MAIN_BONUS:.c=.o)

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

RM				=	rm -f

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

# bonus:			$(OBJS_BONUS) $(HEADER_BONUS)
# 				$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS) -lpthread

all:			$(NAME)

clean:
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean all

.PHONY:			all bonus clean fclean re