HEADER			=	includes/philo_bonus.h

NAME			=	philo_bonus

MAIN			=	main.c

SRCS			=	srcs/ft_calloc.c\
					srcs/ft_free.c\
					srcs/ft_get_current_time.c\
					srcs/ft_msleep.c\
					srcs/ft_parse_args.c\
					srcs/ft_philo_semaphore.c\
					srcs/ft_print_state.c

OBJS			=	$(SRCS:.c=.o)\
					$(MAIN:.c=.o)

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

RM				=	rm -f

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

all:			$(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re