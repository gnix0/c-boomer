#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    double min_scale;
    double scroll_speed;
    double drag_friction;
    double scale_friction;
} Config;

extern const Config defaultConfig;

Config loadConfig(const char *filePath);
int generateDefaultConfig(const char *filePath);

#endif
