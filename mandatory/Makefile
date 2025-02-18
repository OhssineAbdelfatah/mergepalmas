CC = cc 

CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g

LIBMLX = ../lib/mlx

#######################################
# FOR LINUX :
# MLXFLAGS_OBJ = -Imlx_linux
# MLXFLAGS_LINK = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz
########################################  


#########################################
# FOR MAC :
##########FOR OLD MLX
# MLXFLAGS_OBJ = -Imlx
# MLXFLAGS_LINK = -L. -lmlx -framework OpenGL -framework AppKit

######### FOR NEW MLX
MLXFLAGS_LINK = $(LIBMLX)/build/libmlx42.a -L /Users/ilaasri/.brew/Cellar/glfw/3.4/lib/ -lglfw -pthread -lm 
# MLXFLAGS_LINK = $(LIBMLX)/build/libmlx42.a -L /goinfre/aohssine/homebrew/Cellar/glfw/3.4/lib/ -lglfw -pthread -lm 
############################################


ASCII_ART = "\033[31m\n"\
"                    (      \n"\
"             )     ))\ )   \n"\
"       (  ( /(  ( /(()/(   \n"\
"  (   ))\ )\()) )\())(_))  \n"\
"  )\ /((_|(_)\ ((_)(_))_   \n"\
" ((_|_))(| |(_)__ (_)   \  \n"\
"/ _|| || | '_ \|_ \ | |) | \n"\
"\__| \_,_|_.__/___/ |___/  \n"\
"  \033[0m "                          

GNL = ../lib/gnl/get_next_line.c ../lib/gnl/get_next_line_utils.c

CONSTRUCTORS = constructors/constructors.c constructors/constructors_2.c \
				constructors/constructors_bonus.c constructors/constructors_tools_bonus.c

BONUS_FILES = 	game/draw_mini_map_pro.c game/bonus.c \
				game/drawing_things_bonus.c game/floor_ceilling_bonus.c \
				game/shooting_animation_bonus.c

GAME_FILES = game/hooks_nd_loops.c game/casting_tools_2.c  game/casting.c game/casting_tools.c  game/tools_2.c\
			game/tools.c game/walls_rendering.c game/rays.c \
			game/drawing.c game/player_move_hooks.c\
			game/player_move.c \
			game/game.c

CLEANING = cleaning_nd_freeing/freedom.c cleaning_nd_freeing/freedom_part2.c \
			cleaning_nd_freeing/freedom_part3.c

TEXTURES	= game/texture.c game/door_bonus.c			

PARSING = 	parsing/cub.c          parsing/infos_utils2.c parsing/infos_utils3.c \
			parsing/map_check.c	\
			parsing/infos_parse.c  parsing/list_init.c    parsing/map_parse.c	\
			parsing/valid_map.c    parsing/infos_utils.c  parsing/list_utils.c	\
			parsing/safe_func.c    parsing/main.c parsing/test.c

ENEMIES_OBJ = obj_enemies/obj_tools_bonus.c obj_enemies/obj_bonus.c\
				obj_enemies/enemies_tools_bonus.c\
				obj_enemies/enemies_bonus.c

PARSING_B = parsing_bonus/cub_bonus.c          parsing_bonus/infos_utils2_bonus.c parsing_bonus/infos_utils3_bonus.c \
			parsing_bonus/map_check_bonus.c		\
			parsing_bonus/infos_parse_bonus.c  parsing_bonus/list_init_bonus.c    parsing_bonus/map_parse_bonus.c	\
			parsing_bonus/valid_map_bonus.c    parsing_bonus/infos_utils_bonus.c  parsing_bonus/list_utils_bonus.c	\
			parsing_bonus/safe_func_bonus.c    parsing_bonus/main.c parsing_bonus/test_bonus.c parsing_bonus/map_tools_bonus.c

CFILES = ${PARSING} ${GNL} ${TEXTURES} ${ENEMIES_OBJ} ${GAME_FILES} ${BONUS_FILES} ${CONSTRUCTORS} ${CLEANING} main.c

CFILESB = ${PARSING_B} ${GNL} ${TEXTURES} ${ENEMIES_OBJ} ${GAME_FILES} ${BONUS_FILES} ${CONSTRUCTORS} ${CLEANING} main.c

OBJ = $(CFILES:.c=.o)
OBJB = $(CFILESB:.c=.o)

NAME = cub3D
NAMEB = cub3D_bonus

My_lib = ../lib/libft/libft.a
Folder_lib = ../lib/libft/

all : $(My_lib) $(NAME)

bonus : $(My_lib) $(NAMEB)

%.o : %.c  Makefile ${HEADERS}
	$(CC)  $(CFLAGS) $(FFLAG)   -c  $< -o $@

$(My_lib) : 
	make -C ${Folder_lib}

$(NAME) : $(OBJ) $(My_lib) 
	$(CC) $^ $(CFLAGS) $(My_lib) $(MLXFLAGS_LINK)  -o $@

$(NAMEB) : $(OBJB) $(My_lib) 
	$(CC) $^ $(CFLAGS) $(My_lib) $(MLXFLAGS_LINK)  -o $@

clean :
	make clean -C ${Folder_lib}
	rm -rf  $(OBJ) $(OBJB)

fclean : clean
	make fclean -C ${Folder_lib}
	rm -rf $(NAME) $(NAMEB)

re : fclean all

.PHONY : all clean fclean re