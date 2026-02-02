#include "../../../inc/miniRT.h"

bool	intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t)
{
    t_cy_ctx	ctx;
    double		t_body;
    double		t_disk;
    bool		hit_body;
    bool		hit_disk;

    if (!cylinder || !t)
        return (false);
    cylinder_ctx_init(&ctx, cylinder);
    if (ctx.radius <= 0.0 || cylinder->height <= 0.0)
        return (false);
    hit_body = cylinder_body_hit(ray, cylinder, &ctx, &t_body);
    hit_disk = cylinder_disk_hit(ray, cylinder, &ctx, &t_disk);
    if (!hit_body && !hit_disk)
        return (false);
    if (hit_body && (!hit_disk || t_body < t_disk))
        *t = t_body;
    else
        *t = t_disk;
    return (true);
}