#include "../inc/miniRT.h"

/* 
  cc -Wall -Wextra -Werror \
  tests/test_intersections.c \
  src/intersections/ray_sphere.c \
  src/intersections/ray_plane.c \
  src/intersections/ray_cylinder.c \
  src/vec3d/*.c \
  -Iinc -Ilibft -Llibft -lft -lm \
  -o test_intersections
./test_intersections

*/

static int	almost_equal(double a, double b, double eps)
{
    return (fabs(a - b) <= eps);
}

static void	expect_hit(const char *name, bool hit, double t, double expected)
{
    if (!hit)
    {
        printf("[FAIL] %s: expected hit, got miss\n", name);
        return ;
    }
    if (!almost_equal(t, expected, 1e-4))
    {
        printf("[FAIL] %s: t=%.10f expected %.10f\n", name, t, expected);
        return ;
    }
    printf("[OK]   %s: t=%.10f\n", name, t);
}

static void	expect_miss(const char *name, bool hit)
{
    if (hit)
        printf("[FAIL] %s: expected miss, got hit\n", name);
    else
        printf("[OK]   %s: miss\n", name);
}

int	main(void)
{
    t_ray	ray;
    double	t;
    bool	hit;

    {
        t_sphere sp;

        sp.center = (t_vec3){0, 0, 0};
        sp.radius = 1.0;

        ray.origin = (t_vec3){0, 0, -3};
        ray.direction = (t_vec3){0, 0, 1};

        t = 0.0;
        hit = intersect_sphere(ray, &sp, &t);
        expect_hit("sphere front hit", hit, t, 2.0);
    }

    {
        t_plane pl;

        pl.point = (t_vec3){0, 0, 0};
        pl.normal = (t_vec3){0, 0, 1};

        ray.origin = (t_vec3){0, 0, -1};
        ray.direction = (t_vec3){0, 0, 1};

        t = 0.0;
        hit = intersect_plane(ray, &pl, &t);
        expect_hit("plane hit", hit, t, 1.0);
    }

    {
        t_cylinder cy;

        cy.center = (t_vec3){0, 0, 0};
        cy.axis = (t_vec3){0, 0, 1};
        cy.diameter = 2.0;
        cy.height = 2.0;

        ray.origin = (t_vec3){2, 0, 0};
        ray.direction = (t_vec3){-1, 0, 0};

        t = 0.0;
        hit = intersect_cylinder(ray, &cy, &t);
        expect_hit("cylinder body hit", hit, t, 1.0);
    }

    {
        t_cylinder cy;

        cy.center = (t_vec3){0, 0, 0};
        cy.axis = (t_vec3){0, 0, 1};
        cy.diameter = 2.0;
        cy.height = 2.0;

        ray.origin = (t_vec3){0, 0, 2};
        ray.direction = (t_vec3){0, 0, -1};

        t = 0.0;
        hit = intersect_cylinder(ray, &cy, &t);
        expect_hit("cylinder top cap hit", hit, t, 1.0);
    }

    {
        t_cylinder cy;

        cy.center = (t_vec3){0, 0, 0};
        cy.axis = (t_vec3){0, 0, 1};
        cy.diameter = 2.0;
        cy.height = 2.0;

        ray.origin = (t_vec3){2, 0, 2};
        ray.direction = (t_vec3){1, 0, 0};

        t = 0.0;
        hit = intersect_cylinder(ray, &cy, &t);
        expect_miss("cylinder miss", hit);
    }
    return (0);
}