MAKEFLAGS    = --no-print-directory

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRCS_SHARED = shared_functions.c
SRCS_READ = read_shared_memory.c
SRCS_WRITE = write_shared_memory.c
SRCS_DELETE = delete_shared_memory.c

OBJS_SHARED = $(addprefix obj/, $(SRCS_SHARED:.c=.o))
OBJS_READ = $(addprefix obj/, $(SRCS_READ:.c=.o))
OBJS_WRITE = $(addprefix obj/, $(SRCS_WRITE:.c=.o))
OBJS_DELETE = $(addprefix obj/, $(SRCS_DELETE:.c=.o))

TARGET_READ = read_shared_memory
TARGET_WRITE = write_shared_memory
TARGET_DELETE = delete_shared_memory

all: $(TARGET_READ) $(TARGET_WRITE) $(TARGET_DELETE)

$(TARGET_READ): $(OBJS_READ) $(OBJS_SHARED)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_WRITE): $(OBJS_WRITE) $(OBJS_SHARED)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_DELETE): $(OBJS_DELETE) $(OBJS_SHARED)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj/

fclean: clean
	@./$(TARGET_DELETE)
	@rm -f $(TARGET_READ) $(TARGET_WRITE) $(TARGET_DELETE)

re: fclean all

.PHONY: all clean fclean re
