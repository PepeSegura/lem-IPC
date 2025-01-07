MAKEFLAGS    = --no-print-directory

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRCS_SHARED = shared_functions.c
SRCS_MAIN_1 = main1.c
SRCS_MAIN_2 = main2.c

OBJS_SHARED = $(addprefix obj/, $(SRCS_SHARED:.c=.o))
OBJS_MAIN_1 = $(addprefix obj/, $(SRCS_MAIN_1:.c=.o))
OBJS_MAIN_2 = $(addprefix obj/, $(SRCS_MAIN_2:.c=.o))

TARGET_MAIN_1 = main1
TARGET_MAIN_2 = main2

all: $(TARGET_MAIN_1) $(TARGET_MAIN_2) $(TARGET_DELETE)

$(TARGET_MAIN_1): $(OBJS_MAIN_1) $(OBJS_SHARED)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_MAIN_2): $(OBJS_MAIN_2) $(OBJS_SHARED)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj/

fclean: clean
	@rm -f $(TARGET_MAIN_1) $(TARGET_MAIN_2)

re: fclean all

.PHONY: all clean fclean re
