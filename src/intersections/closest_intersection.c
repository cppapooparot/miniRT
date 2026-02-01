#include "../../inc/intersections.h"
#include "../../libft/libft.h"

static t_vec3	vec3_normalize_safe(t_vec3 v)
{
    double	len2;

    len2 = vec3_dot(v, v);
    if (len2 < EPSILON)
        return ((t_vec3){0, 0, 0});
    return (vec3_scale(v, 1.0 / sqrt(len2)));
}

static t_vec3	face_forward(t_vec3 n, t_vec3 ray_dir)
{
    if (vec3_dot(n, ray_dir) > 0.0)
        return (vec3_scale(n, -1.0));
    return (n);
}

static t_vec3	cylinder_normal_at(t_cylinder *cy, t_vec3 p)
{
    double	half_h;
    double	y;
    t_vec3	cp;
    t_vec3	axis;
    t_vec3	q;
    t_vec3	n;
    double	disk_tol;

    axis = cy->axis;
    half_h = cy->height * 0.5;
    disk_tol = EPSILON * 100.0;
    cp = vec3_subtract(p, cy->center);
    y = vec3_dot(cp, axis);
    if (fabs(y - half_h) <= disk_tol)
        return (axis);
    if (fabs(y + half_h) <= disk_tol)
        return (vec3_scale(axis, -1.0));
    q = vec3_add(cy->center, vec3_scale(axis, y));
    n = vec3_subtract(p, q);
    return (vec3_normalize(n));
}

bool	find_closest_intersection(t_ray ray, t_scene *scene, t_hit_record *rec)
{
    t_list	*node;
    double	best_t;

    if (!scene || !rec)
        return (false);

    rec->hit = false;
    best_t = DBL_MAX;

    // spheres
    node = scene->spheres;
    while (node)
    {
        t_sphere	*sp;
        double		t;

        sp = (t_sphere *)node->content;
        if (intersect_sphere(ray, sp, &t) && t < best_t)
        {
            t_vec3	p;
            t_vec3	n;
            best_t = t;
            rec->hit = true;
            rec->t = t;
            p = vec3_add(ray.origin, vec3_scale(ray.direction, t));
            rec->point = p;
            n = vec3_normalize_safe(vec3_subtract(p, sp->center));
            rec->normal = face_forward(n, ray.direction);
            rec->color = sp->color;
        }
        node = node->next;
    }

    // planes
    node = scene->planes;
    while (node)
    {
        t_plane	*pl;
        double	t;

        pl = (t_plane *)node->content;
        if (intersect_plane(ray, pl, &t) && t < best_t)
        {
            t_vec3	p;
            t_vec3	n;
            best_t = t;
            rec->hit = true;
            rec->t = t;
            p = vec3_add(ray.origin, vec3_scale(ray.direction, t));
            rec->point = p;
            n = vec3_normalize_safe(pl->normal);
            rec->normal = face_forward(n, ray.direction);
            rec->color = pl->color;
        }
        node = node->next;
    }

    // cylinders
    node = scene->cylinders;
    while (node)
    {
        t_cylinder	*cy;
        double		t;

        cy = (t_cylinder *)node->content;
        if (intersect_cylinder(ray, cy, &t) && t < best_t)
        {
            t_vec3	p;
            t_vec3	n;

            best_t = t;
            rec->hit = true;
            rec->t = t;
            p = vec3_add(ray.origin, vec3_scale(ray.direction, t));
            rec->point = p;
            n = cylinder_normal_at(cy, p);
            rec->normal = face_forward(n, ray.direction);
            rec->color = cy->color;
        }
        node = node->next;
    }
    return (rec->hit);
}