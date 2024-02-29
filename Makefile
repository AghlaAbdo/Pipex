NAME 		= pipex
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT_L		= ./Libft/libft.a
HEADER		= ./Mandatory/pipex.h
HEADER_BONS	= ./Bonus/pipex_bonus.h
HEADER_GNL	= ./get_next_line/get_next_line.h

SRCS		= ./Mandatory/main.c	\
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

bonus: libft $(NAME) 

ifeq ($(MAKECMDGOALS),bonus)
    $(NAME): $(OBJS_BONS) $(OBJS_GNL) $(LIBFT_L)
		@echo "Building $@.."
		@$(CC) $(CFLAGS) $(LIBFT_L) $(OBJS_BONS) $(OBJS_GNL) -o $@

else
    $(NAME): $(OBJS) $(LIBFT_L)
		@echo "Building $@.."
		@$(CC) $(CFLAGS) $(LIBFT_L) $(OBJS) -o $@
endif

libft:
	@make -C Libft

get_next_line/%.o: get_next_line/%.c $(HEADER_GNL)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

%_bonus.o: %_bonus.c $(HEADER_BONS) $(OBJS_GNL) $(LIBFT_L)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEADER) $(LIBFT_L) 
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removed object files"
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONS)
	@rm -f $(OBJS_GNL)
	@make -C Libft clean

fclean: clean
	@echo "Removed executable"
	@rm -f $(NAME)
	@rm -f $(LIBFT_L)

re: fclean all

.PHONY: all bonus libft clean fclean re