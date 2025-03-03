MAKEFLAGS    = --no-print-directory --silent

NAME_DISPLAY = display
NAME_GAME  	 = lemipc
NAME_DEL	 = clear_memory

CFLAGS       = -Wextra -Wall -Werror
CFLAGS      += -I inc -I inc/display -I inc/game
CFLAGS      += -I libft
CFLAGS      += -O3

DEBUG        = -g3 -fsanitize=address

CPPFLAGS     = -MMD

LIBMLX       = ./libs/MLX42
LIBFT        = ./libs/libft

HEADERS      = -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/inc

LIBS         = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBS        += $(LIBFT)/libft.a

SHARED		=											\
				srcs/shared/errors.c					\
               	srcs/shared/shmemory.c					\
               	srcs/shared/tools.c						\

DISPLAY      = 											\
				srcs/display/main.c						\
														\
               	srcs/display/mlx/init_mlx.c				\
               	srcs/display/mlx/hooks.c				\
               	srcs/display/mlx/draw.c					\
														\
				srcs/display/init_data/shared_memory.c	\
														\
               	$(SHARED)

GAME       = 											\
				srcs/game/main.c						\
														\
				srcs/game/parser/parser.c				\
														\
				srcs/game/init_game/init_game.c			\
				srcs/game/init_player/init_player.c		\
				srcs/game/init_game/init_structs.c		\
														\
				srcs/game/opponents/find_nearest.c		\
														\
				srcs/game/mlx/init_mlx.c				\
               	srcs/game/mlx/hooks.c					\
               	$(SHARED)

DEL_MEM		 =	srcs/clear_memory/main.c 				\
               	$(SHARED)


OBJS_D       = $(patsubst srcs/%.c, objs/srcs/%.o, $(DISPLAY))
OBJS_G       = $(patsubst srcs/%.c, objs/srcs/%.o, $(GAME))
OBJS_DEL       = $(patsubst srcs/%.c, objs/srcs/%.o, $(DEL_MEM))

DEPS_D       = $(OBJS_D:.o=.d)
DEPS_G       = $(OBJS_G:.o=.d)
DEPS_DEL     = $(OBJS_DEL:.o=.d)

all: $(NAME_DISPLAY) $(NAME_GAME) $(NAME_DEL)

MLX_LIB = $(LIBMLX)/build/libmlx42.a

$(MLX_LIB):
	@cmake -DDEBUG=0 $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

LIBFT_LIB = $(LIBFT)/libft.a

$(LIBFT_LIB):
	@make -C $(LIBFT)

$(NAME_DISPLAY): $(MLX_LIB) $(LIBFT_LIB) $(OBJS_D)
	$(CC) $(DEBUG) $(OBJS_D) $(LIBS) $(HEADERS) -o $(NAME_DISPLAY) && printf "Linking: $(NAME_DISPLAY)\n"

$(NAME_GAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJS_G)
	$(CC) $(DEBUG) $(OBJS_G) $(LIBS) $(HEADERS) -o $(NAME_GAME) && printf "Linking: $(NAME_GAME)\n"

$(NAME_DEL): $(MLX_LIB) $(LIBFT_LIB) $(OBJS_DEL)
	$(CC) $(DEBUG) $(OBJS_DEL) $(LIBS) $(HEADERS) -o $(NAME_DEL) && printf "Linking: $(NAME_DEL)\n"

objs/srcs/%.o: ./srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf objs
	@rm -rf $(LIBMLX)/build
	@make fclean -C $(LIBFT)
	@./$(NAME_DEL) 2>/dev/null || true

fclean: clean
	@rm -rf $(NAME_DISPLAY) $(NAME_GAME) $(NAME_DEL)

re: fclean all

-include $(DEPS_D)
-include $(DEPS_G)
-include $(DEPS_DEL)

.PHONY: all clean fclean re
