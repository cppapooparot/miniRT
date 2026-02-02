#include "../../../inc/intersections.h"

bool	cylinder_body_hit(t_ray ray, t_cylinder *cylinder, t_cy_ctx *ctx,
		double *t_hit)
{
	t_cy_body	body;
	t_vec3		point;
	double		axis_pos;

	cylinder_body_init(&body, ray, cylinder, ctx);
	if (!cylinder_body_solve(&body))
		return (false);
	point = ray_point_at(ray, body.t0);
	axis_pos = vec3_dot(vec3_subtract(point, cylinder->center), ctx->axis);
	if (body.t0 > EPSILON && axis_pos >= -ctx->half_h
		&& axis_pos <= ctx->half_h)
		return (*t_hit = body.t0, true);
	point = ray_point_at(ray, body.t1);
	axis_pos = vec3_dot(vec3_subtract(point, cylinder->center), ctx->axis);
	if (body.t1 > EPSILON && axis_pos >= -ctx->half_h
		&& axis_pos <= ctx->half_h)
		return (*t_hit = body.t1, true);
	return (false);
}

bool	cylinder_disk_hit(t_ray ray, t_cylinder *cylinder, t_cy_ctx *ctx,
		double *t_hit)
{
	t_vec3	disk_center;
	double	closest_t;
	double	t_disk;
	bool	hit;

	if (!t_hit)
		return (false);
	hit = false;
	disk_center = vec3_add(cylinder->center, vec3_scale(ctx->axis,
				ctx->half_h));
	if (intersect_disk(ray, disk_center, ctx->axis, ctx->radius, &t_disk))
	{
		closest_t = t_disk;
		hit = true;
	}
	disk_center = vec3_subtract(cylinder->center, vec3_scale(ctx->axis,
				ctx->half_h));
	if (intersect_disk(ray, disk_center, vec3_scale(ctx->axis, -1.0),
			ctx->radius, &t_disk))
	{
		if (!hit || t_disk < closest_t)
			closest_t = t_disk;
		hit = true;
	}
	if (!hit)
		return (false);
	*t_hit = closest_t;
	return (true);
}

bool	intersect_disk(t_ray ray, t_vec3 disk_center, t_vec3 disk_normal,
		double radius, double *t_hit)
{
	t_disk_intersect d;

	if (!t_hit)
		return (false);
	d.denom = vec3_dot(ray.direction, disk_normal);
	if (fabs(d.denom) < EPSILON)
		return (false);
	d.t = vec3_dot(vec3_subtract(disk_center, ray.origin), disk_normal)
		/ d.denom;
	if (d.t <= EPSILON)
		return (false);
	d.p = ray_point_at(ray, d.t);
	d.v = vec3_subtract(d.p, disk_center);
	d.in_plane = vec3_subtract(d.v, project_on_axis(d.v, disk_normal));
	d.dist_square = vec3_length_squared(d.in_plane);
	if (d.dist_square > radius * radius)
		return (false);
	*t_hit = d.t;
	return (true);
}