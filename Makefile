NAME = get_next_line
CC = clang -g
CFLAGS = -Wall -Wextra -Werror -g3
HEADER = get_next_line.h
SRCS =	get_next_line.c main.c \
		get_next_line_utils.c




all:	$(NAME)

$(NAME):
	@clear && $(CC) $(CFLAGS) *.c -D BUFFER_SIZE=42 -o $@

run:	re
	@./$(NAME) 

clean:
	rm -rf $(OBJS)

fclean: 	clean
	$(RM) $(NAME)

re: 	fclean all

valg:
	clear && valgrind --leak-check=full --show-leak-kinds=all ./get_next_line

.PHONY: re fclean clean all