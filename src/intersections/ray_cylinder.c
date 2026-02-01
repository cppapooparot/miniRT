#include "../../inc/intersections.h"

static t_vec3   project_on_axis(t_vec3 v, t_vec3 axis)
{
    return (vec3_scale(axis, vec3_dot(v, axis)));
}

static bool intersect_disk(t_ray ray, t_vec3 disk_center, t_vec3 disk_normal, double radius, double *t_hit)
{
    double denom;
    double t;
    t_vec3 p;
    t_vec3 v;
    t_vec3 in_plane;
    double dist_square;

    if (!t_hit)
        return (false);
    denom = vec3_dot(ray.direction, disk_normal);
    if (fabs(denom) < EPSILON)
        return (false);
    t = vec3_dot(vec3_subtract(disk_center, ray.origin), disk_normal) / denom;
    if (t < EPSILON)
        return (false);
    p = vec3_add(ray.origin, vec3_scale(ray.direction, t));
    v = vec3_subtract(p, disk_center);
    in_plane = vec3_subtract(v, project_on_axis(v, disk_normal));
    dist_square = vec3_length_squared(in_plane);
    if (dist_square > radius * radius)
        return (false);
    *t_hit = t;
    return (true);
}

bool	intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t)
{
    double	radius;
    double	half_height;
    t_vec3	axis;
    t_vec3	oc;
    double	d_dot_a;
    double	oc_dot_a;
    t_vec3	d_perp;
    t_vec3	oc_perp;
    double	A, B, C;
    double	discriminant;
    double	sqrt_d;
    double	best_t;
    bool	hit_any;

    if (!cylinder || !t)
        return (false);
    axis = cylinder->axis;
    radius = cylinder->diameter * 0.5;
    half_height = cylinder->height * 0.5;
    if (radius <= 0.0 || cylinder->height <= 0.0)
        return (false);
    best_t = 0.0;
    hit_any = false;
    // body intersection
    oc = vec3_subtract(ray.origin, cylinder->center);
    d_dot_a = vec3_dot(ray.direction, axis);
    oc_dot_a = vec3_dot(oc, axis);
    d_perp = vec3_subtract(ray.direction, vec3_scale(axis, d_dot_a));
    oc_perp = vec3_subtract(oc, vec3_scale(axis, oc_dot_a));
    A = vec3_dot(d_perp, d_perp);
    B = 2.0 * vec3_dot(oc_perp, d_perp);
    C = vec3_dot(oc_perp, oc_perp) - (radius * radius);
    if (A > EPSILON)
    {
        discriminant = (B * B) - (4.0 * A * C);
        if (discriminant >= 0.0)
        {
            double	t0, t1;
            sqrt_d = sqrt(discriminant);
            t0 = (-B - sqrt_d) / (2.0 * A);
            t1 = (-B + sqrt_d) / (2.0 * A);
            if (t0 > t1)
            {
                double tmp = t0;
                t0 = t1;
                t1 = tmp;
            }
            if (t0 > EPSILON)
            {
                t_vec3	p;
                double	y;
                p = vec3_add(ray.origin, vec3_scale(ray.direction, t0));
                y = vec3_dot(vec3_subtract(p, cylinder->center), axis);
                if (y >= -half_height - EPSILON && y <= half_height + EPSILON)
                {
                    best_t = t0;
                    hit_any = true;
                }
            }
            if (!hit_any && t1 > EPSILON)
            {
                t_vec3	p;
                double	y;
                p = vec3_add(ray.origin, vec3_scale(ray.direction, t1));
                y = vec3_dot(vec3_subtract(p, cylinder->center), axis);
                if (y >= -half_height - EPSILON && y <= half_height + EPSILON)
                {
                    best_t = t1;
                    hit_any = true;
                }
            }
        }
    }
    // disks
    {
        t_vec3	top_center;
        t_vec3	bottom_center;
        double	t_disk;

        top_center = vec3_add(cylinder->center, vec3_scale(axis, half_height));
        bottom_center = vec3_subtract(cylinder->center, vec3_scale(axis, half_height));
        if (intersect_disk(ray, top_center, axis, radius, &t_disk))
        {
            if (!hit_any || t_disk < best_t)
            {
                best_t = t_disk;
                hit_any = true;
            }
        }
        if (intersect_disk(ray, bottom_center, vec3_scale(axis, -1.0), radius, &t_disk))
        {
            if (!hit_any || t_disk < best_t)
            {
                best_t = t_disk;
                hit_any = true;
            }
        }
    }
    if (!hit_any)
        return (false);
    *t = best_t;
    return (true);
}