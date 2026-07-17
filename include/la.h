#ifndef LA_H
#define LA_H

typedef struct {
    double x_axis;
    double y_axis;
} Vec2f;

Vec2f vec_create(double x, double y);
Vec2f vec_scale(Vec2f v, double s);
Vec2f vec_div_scalar(Vec2f v, double s);
Vec2f vec_mul(Vec2f v1, Vec2f v2);
Vec2f vec_div(Vec2f v1, Vec2f v2);
Vec2f vec_add(Vec2f v1, Vec2f v2);
Vec2f vec_sub(Vec2f v1, Vec2f v2);
void vec_add_assign(Vec2f *v1, Vec2f v2);
void vec_sub_assign(Vec2f *v1, Vec2f v2);
double vec_length(Vec2f v);
Vec2f vec_normalize(Vec2f v);

#endif
