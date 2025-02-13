#ifndef PS_H
#define PS_H

#include <stdio.h>
// #include <mlx.h>
#include <math.h>
#include "parsing.h"
#include "macros.h"
#include "game_structs.h"




void shoot_the_rays(t_main_s * var);
int need_update(t_main_s *main, t_player_infos * var, char **map);

int is_there_a_wall(double new_y, double new_x, char **map);
int check_teleportation(t_player_infos *var, char **map);

/*************************************************/
//            >>    TEXTURES.C     <<
/*************************************************/

int calc_x_img(int hor_or_ver, t_ray_info *ray, double wall_hiegt, double img_w);
int calc_y_img(int y_proj ,int wall_hiegt , int img_h);


/*************************************************/
//            >>    DRAWING.C     <<
/*************************************************/

void draw_square(t_main_s *var, int x, int y);
void draw_a_line(t_main_s *var, int s_x, int s_y, int f_x, int f_y, int color);
void  draw_empty_square(t_main_s *var,int  y, int x);
void draw_disk(t_main_s *var, int x_c, int y_c, int radius);
void draw_disk1(t_main_s *var, int x_c, int y_c, int radius);
void draw_disk11(mlx_image_t *img ,int x_c, int y_c, int radius, int color);
void draw_disk2(t_test *var, int x_c, int y_c, int radius);
void draw_disk3(t_test *var, int x_c, int y_c, int radius);
void draw_square_for_mini(mlx_image_t *img, int x, int y, int color);
void  draw_empty_square_for_mini(mlx_image_t *img,  int  y, int x);
void draw_a_line2(t_main_s *var, int s_x, int s_y, int f_x, int f_y, int color, mlx_image_t *img);

/*************************************************/
//            >>    DRAW_MINI_MAP.C     <<
/*************************************************/

int draw_the_mini_map(t_main_s *var);

/*************************************************/
//            >>    CONSTRUCTORS.C     <<
/*************************************************/

t_main_s *init_main_var(t_parse_data *parse);
t_player_infos *init_player_struct(t_main_s *ptr, char c, int x, int y);
t_ray_info *init_rays(t_main_s *ptr, double ray_angle, double ray_increment);
t_walls *init_walls(t_main_s *ptr);


t_text *get_image(mlx_texture_t *text);
int **gat_pixles(mlx_texture_t* img, int w, int h);
/*************************************************/
//            >>    TOOLS.C     <<
/*************************************************/

int ft_dstr_len(char **av);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
double adjust_angle(double angle);
void panic(char *s);
int is_it_the_player(char c);



/*************************************************/
//            >>   CASTING.C     <<
/*************************************************/
void init_cst_vert(t_casting *cst, t_main_s *var, int i);
void init_cst_horiz(t_casting *cst, t_main_s *var, int i);
// int hit_a_wall(t_casting *cst, t_main_s *var, int i, int ref);
double cast_vertically(t_main_s *var, int i, t_x_and_y_d *xy, t_x_and_y_d* door_xy);
double cast_horizontally(t_main_s *var, int i, t_x_and_y_d *xy, t_x_and_y_d* door_xy);
int hit_a_wall(t_main_s *var, double xintersection, double yintersection, int i);
int hit_a_door(t_main_s *var, double xintersection, double yintersection, int i);

/*************************************************/
//            >>   HOOKS_ND_LOOPS.C     <<
/*************************************************/
// int key_hook(int key, t_main_s *ptr);
void key_hook(mlx_key_data_t key, void *var);
// int loop_hook(t_main_s *var);
void loop_hook(void *ptr);
void mlx_loops_and_hooks(t_main_s *var);

/*-------------DIRECTIONS-----------*/
int         turn_left(t_main_s *ptr);
int        turn_right(t_main_s *ptr);
int        go_back(t_main_s *ptr);
int        go_forward(t_main_s *ptr);


/****************************************************/
//          >> DRAW_MINI_MAP  <<
/****************************************************/
int draw_mini_map_42(t_main_s *var);

/****************************TMP************ */
void fill_map(char **av,t_main_s *var);
void work_of_art(t_main_s *var, int shoot);
void wall_rendering(t_main_s *var);
// void paintit(mlx_image_t *img, int color, int hight, int width);
void paintit(mlx_image_t *img, int color, t_xy_i *start, t_xy_i *till);


/************************************************************/
//                      >> BONUS.C <<
/************************************************************/


void fps_hands_rendring(t_main_s *var);
void draw_crosshairs(t_main_s *var, int len ,int width, int color);
void obj_rebdering(t_main_s *var);
int get_color(t_main_s *var, t_text *img, int x, int y);

void count_obj_enemi(t_main_s *var);
t_player_bonus *init_player_bonus(t_main_s *var, t_player_infos *ptr);



int get_color_obj(t_main_s *var, int obj_height, int obj_width, int x, int y);
void update_obj_data(t_main_s *var,  t_player_infos *p_var, t_obj *obj,int nbr_obj);
void render_objects(t_main_s *var, t_player_bonus *p_ptr);

double calculate_obj_or_enemy_teta(t_player_infos *p_var, t_obj *obj, t_enemy *enemy);
double get_distance(t_player_infos *p_var, double x, double y);
void update_enemy_data(t_main_s *var, t_player_infos *p_var, t_enemy *enemy,int nbr_enemy);
void render_enemies(t_main_s *var, t_player_bonus *p_ptr);
void adjust_rank_enemies(t_enemy *enemy, int max);

long long	get_time_mil(void);
void draw_health_bar(t_main_s *var);
void shoot_them_mfs(t_main_s *var);
void redisplay_the_gun(t_main_s * var);



/************************************************************/
//                      >> FLOOR_CEILING-BONUS.C <<
/************************************************************/

void draw_floor(t_main_s *var, int x, int y, int nbr_ray);
void render_sky(t_main_s *var, int x, int y_end, int nbr_ray);

/************************************************************/
//                      >> FREEDOM.C <<
/************************************************************/

void free_rays_bonus(t_ray_info *var);
void free_rays(t_main_s *var);

/************************************************************/
//                      >> DOOR_BONUS.C <<
/************************************************************/

int is_there_door(t_rays_bonus* ray, t_main_s *var, int ray_nbr);
void    draw_door(t_main_s *var,t_walls *walls, int i, int j, double offset);
void free_p_info(t_player_infos *player, t_main_s *var);
void        free_p_bonus(t_player_bonus* player_b);
void free_minimap(t_main_s *var ,t_mini_map *mini_map);
void free_text(t_text *text);
void free_texts(t_text **text);
void free_d_arr(char **av);
void free_main_bonus(t_bonus *var, t_main_s *main);
void reset_them_all(t_main_s * var);
void free_all(t_main_s *var);

#endif