#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

# include "scene.h"
# include "vec3d.h"
# include <stdbool.h>

typedef enum e_hit_type
{
    HIT_NONE = 0,
    HIT_SPHERE,
    HIT_PLANE,
    HIT_CYLINDER
}   t_hit_type;

typedef struct s_hit_record
{
    bool        hit;
    double      t; // ray parameter
    t_vec3      point;
    t_vec3      normal;
    t_rgb       color;
    t_hit_type  type;
}   t_hit_record;

typedef struct s_sphere_intersect
{
    double              epsilon;
    t_vec3			    oc;  // vector from centre of the sphere to start of the ray
    double			    a;
    double			    b;
    double			    c;
    double			    discriminant;
    double			    sqrt_d;
    double			    t0;
    double			    t1;
}   t_sphere_intersect;

bool    intersect_sphere(t_ray ray, t_sphere *sphere, double *t);
bool    intersect_plane(t_ray ray, t_plane *plane, double *t);
bool    intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t);

bool    find_closest_intersection(t_ray ray, t_scene *scene, t_hit_record *rec);

#endif

