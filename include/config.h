#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    double min_scale;
    double scroll_speed;
    double drag_friction;
    double scale_friction;
} Config;

extern const Config DEFAULT_CONFIG;

Config load_config(const char *filePath);
int generate_default_config(const char *filePath);

#endif
