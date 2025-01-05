MAKEFLAGS    = --no-print-directory --silent

NAME_DISPLAY = display
NAME_PLAYER  = player

CFLAGS       = -Wextra -Wall -Werror
CFLAGS      += -I inc -I inc/display -I inc/player
CFLAGS      += -I libft
CFLAGS      += -O3

DEBUG        = -g3 -fsanitize=address,leak

CPPFLAGS     = -MMD

LIBMLX       = ./libs/MLX42
LIBFT        = ./libs/libft

HEADERS      = -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/inc

LIBS         = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBS        += $(LIBFT)/libft.a

DISPLAY      = 									\
				srcs/display/main.c				\
												\
               	srcs/display/mlx/hooks.c		\
               	srcs/display/mlx/hooks_tools.c	\
												\
               	srcs/display/other/errors.c		\

PLAYER       = 									\
				srcs/player/main.c				\
												\

OBJS_D       = $(patsubst srcs/%.c, objs/srcs/%.o, $(DISPLAY))
OBJS_P       = $(patsubst srcs/%.c, objs/srcs/%.o, $(PLAYER))

DEPS_D       = $(OBJS_D:.o=.d)
DEPS_P       = $(OBJS_P:.o=.d)

all: $(NAME_DISPLAY) $(NAME_PLAYER)

libmlx:
	@cmake -DDEBUG=1 $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

$(NAME_DISPLAY): libmlx libft $(OBJS_D)
	$(CC) $(DEBUG) $(OBJS_D) $(LIBS) $(HEADERS) -o $(NAME_DISPLAY) && printf "Linking: $(NAME_DISPLAY)\n"

$(NAME_PLAYER): libmlx libft $(OBJS_P)
	$(CC) $(DEBUG) $(OBJS_P) $(LIBS) $(HEADERS) -o $(NAME_PLAYER) && printf "Linking: $(NAME_PLAYER)\n"

objs/srcs/%.o: ./srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf objs
	@rm -rf $(LIBMLX)/build
	@make fclean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME_DISPLAY) $(NAME_PLAYER)

re: fclean all

-include $(DEPS_D) $(DEPS_P)

.PHONY: all clean fclean re libmlx libft
