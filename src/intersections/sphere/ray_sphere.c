#include "../../../inc/miniRT.h"

static bool	sp_calculate(t_sphere_intersect *sp, t_ray ray, t_sphere *sphere)
{
    if (!sp || !sphere)
        return (false);
    sp->oc = vec3_subtract(ray.origin, sphere->center);
    sp->a = vec3_dot(ray.direction, ray.direction);
    if (sp->a < EPSILON)
        return (false);
    sp->b = 2.0 * vec3_dot(sp->oc, ray.direction);
    sp->c = vec3_dot(sp->oc, sp->oc) - (sphere->radius * sphere->radius);
    sp->discriminant = (sp->b * sp->b) - (4.0 * sp->a * sp->c);
    if (sp->discriminant < 0.0)
        return (false);
    sp->sqrt_d = sqrt(sp->discriminant);
    sp->t0 = (-sp->b - sp->sqrt_d) / (2.0 * sp->a);
    sp->t1 = (-sp->b + sp->sqrt_d) / (2.0 * sp->a);
    return (true);
}

bool	intersect_sphere(t_ray ray, t_sphere *sphere, double *t)
{
    t_sphere_intersect	sp;

    if (!sphere || !t)
        return (false);
    if (!sp_calculate(&sp, ray, sphere))
        return (false);
    if (sp.t0 > EPSILON && sp.t1 > EPSILON)
    {
        if (sp.t0 < sp.t1)
            *t = sp.t0;
        else
            *t = sp.t1;
    }
    else if (sp.t0 > EPSILON)
        *t = sp.t0;
    else if (sp.t1 > EPSILON)
        *t = sp.t1;
    else
        return (false);
    return (true);
}