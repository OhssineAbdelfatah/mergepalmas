#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include <stdbool.h>
#include <sys/time.h>
#include "parsing.h"
#include "ps.h"
#include "../../lib/mlx/include/MLX42/MLX42.h"

typedef struct s_main_struct t_main_s;
typedef struct s_player_infos t_player_infos;
typedef struct	s_data t_data;
typedef struct s_test t_test;
typedef struct s_ray_info t_ray_info ;
typedef struct s_casting t_casting;
typedef struct s_walls_rendering t_walls;
typedef struct s_mini_map t_mini_map;
typedef struct s_textures_imgs t_textures_img;
typedef struct s_x_and_y_d t_x_and_y_d;
typedef struct s_xy_i t_xy_i;
typedef struct s_calc_img t_calc_img;

/********>> BONUS <<*****/
typedef struct s_bonus t_bonus;
typedef struct s_ray_hit_obj t_ray_hit_obj;
typedef struct s_ray_hit_door t_ray_hit_door;
typedef struct s_ray_hit_enemy t_ray_hit_enemy;
typedef struct s_rays_bonus t_rays_bonus;
typedef struct s_player_bonus t_player_bonus;
typedef struct s_obj t_obj;
typedef struct s_enemy t_enemy;
typedef struct timeval			t_time;

// {
//     /* data */
// };



/* TEXTURES */

typedef struct s_img t_img;
typedef struct s_text t_text;

struct s_img {
    double x_img;
    double y_img;
};

struct s_xy_i {
    int x;
    int y;
};

struct s_text {
    int **pixels;
    int width;
    int hieght;
};


/***************************/

struct s_x_and_y_d
{
    double x;
    double y; 
    double distance;
};

struct s_ray_hit_obj
{
    char from;
    double distance;
    double x_intersection;
    double y_intersection;
};

struct s_ray_hit_door
{
    char from;
    double distance;
    double x_intersection;
    double y_intersection;
};

struct s_ray_hit_enemy
{
    double distance;
    double x_intersection;
    double y_intersection;
};


struct s_rays_bonus
{
    bool hit_a_door;
    bool hit_an_obj;
    bool hit_an_enemy;

    t_ray_hit_obj *obj;
    t_ray_hit_door *door;
    t_ray_hit_enemy *enemy;
};


struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};


struct s_mini_map
{
    int p_x;
    int p_y;
    int minimap_width;
    int minimap_height;
    int mini_square_len;
    // t_data img3;
    mlx_image_t *img3;
};


struct s_ray_info
{
    bool facing_up;
    bool facing_left;
    bool facing_right;
    bool facing_down;
    double x_last_intersection;
    double y_last_intersection;
    int x_hor;
    int y_ver;
    double wall_hight;
    int horzt_or_vert;
    double distance;
    double angle;
    char wall_dir;
    t_rays_bonus *bonus_rays;
};

struct s_player_infos
{
    int pov;
    int move_up_down;
    int move_left_right;
    int turn_arround;
    int nbr_rays;
    double x;
    double y;
    double speed;
    double rotation_speed;
    double rotation_angle;
    double fov;
    t_walls *walls;
    t_ray_info *rays;

    /***bonus***/
    bool alive;
    int health;
    int max_health;
    int look_up_down;
    int up_down_offset;
    int jump_kneel;
    t_player_bonus *p_bonus;
};

struct s_textures_imgs
{
    int height;
    int width;
    void *img_ver;
    void *img_hor;
};

struct s_main_struct
{
    int window_width;
    int window_height;
    int map_hight;
    int map_width;
    long long start_frame;
    char **map;
    mlx_t *mlx;
    mlx_image_t *img2;
    mlx_image_t *img3;
    t_text **text;
    t_mini_map *mini_map;
    t_player_infos *p_infos;
    t_parse_data *parse;
    // t_walls *walls;
    /***********/
    //bonus
    /***********/
    // struct timeval tv;
    t_bonus *bonus;

};


struct s_casting
{
    double distance;
    double xsteps;
    double ysteps;
    double xintersection;
    double yintersection;
    double tan_angle;
};


struct s_walls_rendering
{
    double distance_prj_plane;
    double prj_plane_height;
    double wall_hight;
};


struct s_bonus
{
    int nbr_obj;
    int nbr_enemies;
    int mouse_x;
    int mouse_y;
    mlx_texture_t *enemy_mlx_tex;
    mlx_texture_t *dead_enemy_mlx_tex;
    mlx_texture_t *pillar_tex;
    mlx_texture_t *floor;
    mlx_texture_t *sky;
    mlx_texture_t *gun_in_hand[4];
    mlx_texture_t *crosshair;
    t_text *dead_enemy_text;
    t_text *door;
    t_text *enemy_text;
    t_text *floor_text;
    t_text *sky_text;
    t_text *gun_in_hand_text0;
    t_text *pillar_img;
    mlx_image_t *gun_in_hands_img[4];
    mlx_image_t *crosshair_img;
};


struct s_obj
{
    bool visible;
    int x_screen;
    int y_screen;
    double x;
    double y;
    double vector_x;
    double vector_y;
    double vector_teta;
    double obj_teta;
    double obj_height;
    double obj_width;
    double distance;
};

struct s_enemy
{
    bool alive;
    int x_screen;
    int y_screen;
    int enemy_height;
    int enemy_width;
    double x;
    double y;
    double vector_x;
    double vector_y;
    double vector_teta;
    double enemy_teta;
    double distance;
};

struct s_player_bonus
{
    t_obj *obj;
    t_enemy *enemy;
};

struct s_calc_img
{
    double door_h;
    int ray_nbr;
    double img_w;
    double img_door_w;
    t_enemy *enemy;
};






// struct s_test
// {
//     int img_width;
//     int img_hight;
//     int img1_width;
//     int img1_hight;
//     void *mlx;
//     void *win;
//     t_data img;
//     t_data img1;
// };

#endif