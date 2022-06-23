NAME =	miniRT

HEADER = 	main_files/mini_rt.h \
			parser/parser.h \
			parser/analysis.h \
			parser/structures.h \
			vec_func/vec_func.h \
			gnl/get_next_line.h \
			gnl/gnl_systemic.h

SRCS =		main_files/main.c \
			main_files/bmp.c \
			main_files/intersection.c \
			main_files/intersection_tr.c \
			main_files/lighting.c \
			main_files/obstacles.c \
			main_files/painting.c \
			main_files/which_color_put.c \
			parser/parser.c \
			parser/error_func_rt.c \
			parser/par_types_r_c_l_sp.c \
			parser/par_types_tr_cy_pl.c \
			parser/par_types_a_sq.c \
			parser/parser_utils_rt.c \
			parser/scene_operations.c \
			parser/string_validation.c \
			parser/str_val_isvec.c \
			vec_func/vec_func.c \
			vec_func/vec_func2.c \
			vec_func/vec_func3.c \
			vec_func/q_func.c \
			vec_func/q_func2.c \
			gnl/get_next_line.c \
			gnl/get_next_line_utils.c

OBJS =		$(SRCS:.c=.o)

LIBFT =		libft
MLX =		mlx

CC :=		gcc
CFLAGS =	-Wall -Werror -Wextra
MLX_FLAGS =	libmlx.dylib -framework Metal -framework AppKit
LIB_FLAGS =	-L libft -lft
RM =		rm -f

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER) $(LIBFT) $(MLX)
			@make -s -C $(MLX)
			@mv $(MLX)/libmlx.dylib .
			@make -s -C $(LIBFT)
			@$(CC) $(CFLAGS) $(LIB_FLAGS) $(MLX_FLAGS) $(OBJS) -o $(NAME)

clean:
			@ $(RM) $(OBJS)
			@make clean -C $(MLX)
			@make clean -C $(LIBFT)

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) libmlx.dylib
			@$(RM) img.bmp
			@make fclean -C $(LIBFT)

re:		fclean all

norm:
			@norminette $(LIBFT) gnl parser main_files vec_func

.PHONY:	all clean fclean re norm

