NAME 		= pipex
NAME_BONS	= pipex_bonus
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT		=  ./Libft/libft.a
HEADER		= ./Mandatory/pipex.h
HEADER_BONS	= ./Bonus/pipex_bonus.h
HEADER_GNL	= ./get_next_line/get_next_line.h

SRCS		= ./Mandatory/pipex.c	\
			./Mandatory/tools.c

SRCS_BONS	= ./Bonus/main_bonus.c			\
			./Bonus/find_path_bonus.c		\
			./Bonus/handle_pipes_bonus.c	\
			./Bonus/tools_bonus.c			\
			./Bonus/here_doc.c				\

SRCS_GNL	= ./get_next_line/get_next_line.c		\
			./get_next_line/get_next_line_utils.c
				
OBJS		= $(SRCS:.c=.o)
OBJS_BONS	= $(SRCS_BONS:.c=.o)
OBJS_GNL	= $(SRCS_GNL:.c=.o)

all: libft $(NAME)

bonus: libft $(NAME_BONS)

$(NAME): $(OBJS) $(LIBFT) 
	@echo "Building $@.."
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $@

$(NAME_BONS): $(OBJS_BONS) $(OBJS_GNL) $(LIBFT)
	@echo "Building $@.."
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS_BONS) $(OBJS_GNL) -o $@

libft:
	@make -C Libft

get_next_line/%.o: get_next_line/%.c $(HEADER_GNL)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

%_bonus.o: %_bonus.c $(HEADER_BONS) $(OBJS_GNL) $(LIBFT)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEADER) $(LIBFT) 
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