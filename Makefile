NAME 		= pipex
NAME_BONS	= pipex_bonus
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT		=  ./Libft/libft.a
HEADER		= ./Mandatory/pipex.h
HEADER_BONS	= ./Bonus/pipex_bonus.h

SRCS		= ./Mandatory/pipex.c	\
			./Mandatory/tools.c

SRCS_BONS	= ./Bonus/main_bonus.c	\
				
OBJS = $(SRCS:.c=.o)
OBJS_BONS = $(SRCS_BONS:.c=.o)

all: libft $(NAME)

bonus: libft $(NAME_BONS)

$(NAME) : $(OBJS) $(LIBFT) 
	@echo "Building $@.."
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $@

$(NAME_BONS): $(OBJS_BONS) $(LIBFT)
	@echo "Building $@.."
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS_BONS) -o $@

libft:
	@make -C Libft

%_bonus.o:%_bonus.c $(HEADER_BONS) $(LIBFT)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o:%.c $(HEADER) $(LIBFT) 
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removed object files"
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONS)
	@make -C Libft clean

fclean: clean
	@echo "Removed executable"
	@rm -f $(NAME)
	@rm -f $(NAME_BONS)
	@rm -f $(LIBFT)

re: fclean all

.PHONY: all bonus libft clean fclean re