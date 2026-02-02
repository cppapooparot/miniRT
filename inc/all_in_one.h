/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_in_one.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/03 02:06:09 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_IN_ONE_H
# define ALL_IN_ONE_H

/* ========================================================================== */
/*                           EXTERNAL DEPENDENCIES                            */
/* ========================================================================== */

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ========================================================================== */
/*                              MACROS & DEFINES                              */
/* ========================================================================== */

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef _USE_MATH_DEFINES
#  define _USE_MATH_DEFINES
# endif

# define EPSILON 1e-6

/* ========================================================================== */
/*                           LAYER 1: VEC3D (BASE MATH)                       */
/* ========================================================================== */

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef struct s_basis
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
}			t_basis;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}			t_rgb;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

/* Vector operations */
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3		vec3_scale(t_vec3 a, double scalar);
t_vec3		vec3_div(t_vec3 a, double scalar);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
t_vec3		vec3_negate(t_vec3 a);
double		vec3_length(t_vec3 a);
double		vec3_length_squared(t_vec3 a);
t_vec3		vec3_normalize(t_vec3 a);
double		vec3_distance(t_vec3 a, t_vec3 b);
t_vec3		vec3_reflect(t_vec3 v, t_vec3 n);

/* RGB operations */
t_rgb		rgb_add(t_rgb a, t_rgb b);
t_rgb		rgb_scale(t_rgb color, double scalar);
t_rgb		rgb_multiply(t_rgb a, t_rgb b);
t_rgb		rgb_clamp(t_rgb color);
int			rgb_to_int(t_rgb color);

/* ========================================================================== */
/*                        LAYER 2: OBJECTS (GEOMETRIC)                        */
/* ========================================================================== */

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_rgb	color;
}			t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_rgb	color;
}			t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	diameter;
	double	height;
	t_rgb	color;
}			t_cylinder;

typedef struct s_light
{
	t_vec3	position;
	double	brightness;
	t_rgb	color;
}			t_light;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	int		fov;
}			t_camera;

/* ========================================================================== */
/*                          LAYER 3: WINDOW (MLX)                             */
/* ========================================================================== */

typedef struct s_data	t_data;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}						t_mlx;

/* Window operations */
bool					initialize_window(t_mlx *mlx, int width, int height);
void					destroy_window(t_mlx *mlx);
void					mlx_put_pixel(t_mlx *mlx, int x, int y, int color);
int						handle_keypress(int keycode, t_data *data);
int						handle_close(t_data *data);

/* ========================================================================== */
/*                          LAYER 4: SCENE (COMPOSITION)                      */
/* ========================================================================== */

typedef struct s_list	t_list;

typedef struct s_viewport
{
	t_vec3				center;
	t_vec3				upper_left;
	t_vec3				horizontal;
	t_vec3				vertical;
	double				height;
	double				width;
	double				focal_length;
}						t_viewport;

typedef struct s_scene
{
	t_rgb				ambient_light;
	double				ambient_intensity;
	t_camera			*camera;
	t_list				*lights;
	t_list				*spheres;
	t_list				*planes;
	t_list				*cylinders;
	t_viewport			viewport;
}						t_scene;

typedef struct s_data
{
	t_mlx				mlx;
	t_scene				scene;
}						t_data;

/* Scene operations */
bool					initialize_scene(char *filename, t_scene *scene);
bool					clean_scene(t_scene *scene);
t_viewport				setup_viewport(t_camera *camera, int image_width,
							int image_height);
t_ray					generate_ray(t_data *data, int x, int y);
t_rgb					calculate_light(t_scene *scene, t_hit_record *record);
void					tracer_loop(t_data *data);

/* ========================================================================== */
/*                       LAYER 5: INTERSECTIONS (RAY TRACING)                 */
/* ========================================================================== */

typedef enum e_hit_type
{
	HIT_NONE = 0,
	HIT_SPHERE,
	HIT_PLANE,
	HIT_CYLINDER
}				t_hit_type;

typedef struct s_hit_record
{
	bool		hit;
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_rgb		color;
	t_hit_type	type;
	t_cylinder	*cylinder;
	t_sphere	*sphere;
	t_plane		*plane;
}				t_hit_record;

typedef struct s_sphere_intersect
{
	t_vec3		oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		sqrt_d;
	double		t0;
	double		t1;
}				t_sphere_intersect;

typedef struct s_disk_intersect
{
	double		denom;
	double		t;
	t_vec3		p;
	t_vec3		v;
	t_vec3		in_plane;
	double		dist_square;
}				t_disk_intersect;

typedef struct s_cy_ctx
{
	t_vec3		axis;
	double		radius;
	double		half_h;
}				t_cy_ctx;

typedef struct s_cy_body
{
	t_vec3		oc;
	double		d_dot_a;
	double		oc_dot_a;
	t_vec3		d_perp;
	t_vec3		oc_perp;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		sqrt_disc;
	double		t0;
	double		t1;
}				t_cy_body;

/* Intersection functions */
bool			intersect_sphere(t_ray ray, t_sphere *sphere, double *t);
bool			intersect_plane(t_ray ray, t_plane *plane, double *t);
bool			intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t);
bool			find_closest_intersection(t_ray ray, t_scene *scene,
					t_hit_record *rec);

/* Cylinder intersection utilities */
t_vec3			ray_point_at(t_ray ray, double t);
t_vec3			project_on_axis(t_vec3 v, t_vec3 axis);
void			cylinder_ctx_init(t_cy_ctx *ctx, t_cylinder *cylinder);
void			cylinder_body_init(t_cy_body *b, t_ray ray,
					t_cylinder *cylinder, t_cy_ctx *ctx);
bool			cylinder_body_solve(t_cy_body *b);
bool			cylinder_body_hit(t_ray ray, t_cylinder *cylinder,
					t_cy_ctx *ctx, double *t_hit);
bool			cylinder_disk_hit(t_ray ray, t_cylinder *cylinder,
					t_cy_ctx *ctx, double *t_hit);
bool			intersect_disk(t_ray ray, t_vec3 disk_center,
					t_vec3 disk_normal, double radius, double *t_hit);

/* ========================================================================== */
/*                          LAYER 6: PARSER (INPUT)                           */
/* ========================================================================== */

typedef bool	(*t_parse_fn)(char **, t_scene *);

/* Parsing functions */
bool			read_file(char *filename, t_scene *scene);
bool			parse_ambient_light(char **tokens, t_scene *scene);
bool			parse_camera(char **tokens, t_scene *scene);
bool			parse_light(char **tokens, t_scene *scene);
bool			parse_sphere(char **tokens, t_scene *scene);
bool			parse_plane(char **tokens, t_scene *scene);
bool			parse_cylinder(char **tokens, t_scene *scene);
bool			parse_vec3(char *str, t_vec3 *vec);
bool			parse_rgb(char *str, t_rgb *color);

/* Validation functions */
bool			check_file_extension(char *filename);
bool			check_double(const char *str);
bool			check_integer(const char *str);
bool			check_rgb_values(int r, int g, int b);
bool			check_split_length(char **tokens, int expected_length);
bool			check_arg_format(char **tokens, int expected_length,
					bool (*check_func)(const char *));
bool			check_ranged(double value, double min, double max);
bool			check_range_vec3(t_vec3 vec, double min, double max);
bool			put_error(char *message);

/* ========================================================================== */
/*                         END OF ALL_IN_ONE HEADER                           */
/* ========================================================================== */

#endif
