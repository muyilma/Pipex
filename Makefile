NAME=pipex

SRCS= pipex.c
CFLAGS=
LIBFT=libft/libft.a


$(NAME): $(SRCS) 
	make -C ./libft -s
	cc  -o  $(NAME) -g $(SRCS) $(LIBFT) 

all: $(NAME)

clean:
	make clean -C ./libft -s
	

fclean: clean
	make fclean -C ./libft -s
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re