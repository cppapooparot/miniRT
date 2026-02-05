#include "../../../inc/miniRT.h"

t_vec3	ray_point_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}

t_vec3	project_on_axis(t_vec3 v, t_vec3 axis)
{
	return (vec3_scale(axis, vec3_dot(v, axis)));
}

void	cylinder_body_init(t_cy_body *b, t_ray ray, t_cylinder *cylinder)
{
	b->oc = vec3_subtract(ray.origin, cylinder->center);
	b->d_dot_a = vec3_dot(ray.direction, cylinder->axis);
	b->oc_dot_a = vec3_dot(b->oc, cylinder->axis);
	b->d_perp = vec3_subtract(ray.direction, vec3_scale(cylinder->axis,
				b->d_dot_a));
	b->oc_perp = vec3_subtract(b->oc, vec3_scale(cylinder->axis, b->oc_dot_a));
	b->a = vec3_dot(b->d_perp, b->d_perp);
	b->b = 2.0 * vec3_dot(b->oc_perp, b->d_perp);
	b->c = vec3_dot(b->oc_perp, b->oc_perp) - (cylinder->radius
			* cylinder->radius);
}

bool	cylinder_body_solve(t_cy_body *b)
{
	b->disc = (b->b * b->b) - (4.0 * b->a * b->c);
	if (b->a <= EPSILON || b->disc < 0.0)
		return (false);
	b->sqrt_disc = sqrt(b->disc);
	b->t0 = (-b->b - b->sqrt_disc) / (2.0 * b->a);
	b->t1 = (-b->b + b->sqrt_disc) / (2.0 * b->a);
	if (b->t0 > b->t1)
	{
		b->sqrt_disc = b->t0;
		b->t0 = b->t1;
		b->t1 = b->sqrt_disc;
	}
	return (true);
}
