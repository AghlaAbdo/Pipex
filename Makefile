NAME 		= pipex
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT		=  ./Libft/libft.a
HEADER		= ./Mandatory/pipex.h

SRCS		= ./Mandatory/pipex.c
				
OBJS = $(SRCS:.c=.o)

all: libft $(NAME)

$(NAME) : $(OBJS) $(OBJS_GNL) $(LIBFT) 
	@echo "Building $@.."
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $@

libft:
	@make -C Libft

%.o:%.c $(HEADER) $(OBJS_GNL) $(LIBFT) 
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removed object files"
	@rm -f $(OBJS)
	@make -C Libft clean

fclean: clean
	@echo "Removed executable"
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

.PHONY: all bonus libft clean fclean re