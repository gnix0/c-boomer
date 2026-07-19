#include "navigation.h"
#include "config.h"
#include "la.h"
#include <math.h>

Vec2f world(Camera camera, Vec2f v)
{
    return vec_div_scalar(v, camera.scale);
}

void update(Camera *camera, Config config, double dt, Mouse mouse,
            Vec2f window_size)
{
    if (fabs(camera->delta_scale) > 0.5) {
        Vec2f scaled_window_size = vec_scale(window_size, 0.5);

        Vec2f p0 = (vec_div_scalar(
            vec_sub(camera->scale_pivot, scaled_window_size), camera->scale));

        camera->scale =
            fmax(camera->scale + camera->delta_scale * dt, config.min_scale);

        Vec2f p1 = (vec_div_scalar(
            vec_sub(camera->scale_pivot, scaled_window_size), camera->scale));

        camera->position = vec_add(camera->position, vec_sub(p0, p1));

        camera->delta_scale -= camera->delta_scale * dt * config.scale_friction;
    }

    if (!mouse.drag && (vec_length(camera->velocity) > VELOCITY_THRESHOLD)) {
        camera->position =
            vec_add(camera->position, vec_scale(camera->velocity, dt));
        
        camera->velocity =
            vec_sub(camera->velocity, vec_scale(vec_scale(camera->velocity, dt),
                                                config.drag_friction));
    }
}
