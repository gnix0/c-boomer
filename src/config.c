#include "config.h"
#include "string_view.h"
#include <stdio.h>

#define SV_Fmt "%.*s"
#define SV_Arg(s) (int)(s).len, (s).data

const Config DEFAULT_CONFIG = {
    .min_scale = 0.01,
    .scroll_speed = 1.5,
    .drag_friction = 6.0,
    .scale_friction = 4.0,
};

Config load_config(const char *filePath)
{
    Config config = DEFAULT_CONFIG;

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("fopen");
        return config;
    }

    char line[256];
    while (fgets(line, sizeof line, file) != NULL) {
        String_View sv_line = sv(line);
        sv_trim(&sv_line);

        if (sv_line.len == 0 || sv_line.data[0] == '#')
            continue;

        if (!sv_contains(sv_line, '=')) {
            fprintf(stderr, "Missing '=': " SV_Fmt "\n", SV_Arg(sv_line));
            continue;
        }

        String_View key = sv_chop_by_delim(&sv_line, '=');
        String_View value = sv_line;
        sv_trim(&key);
        sv_trim(&value);

        if (key.len == 0) {
            fprintf(stderr, "Missing configuration key\n");
            continue;
        }

        if (value.len == 0) {
            fprintf(stderr, "Missing value for key: " SV_Fmt "\n", SV_Arg(key));
            continue;
        }

        double *destination;
        if (sv_eq_cstr(key, "min_scale"))
            destination = &config.min_scale;
        else if (sv_eq_cstr(key, "scroll_speed"))
            destination = &config.scroll_speed;
        else if (sv_eq_cstr(key, "drag_friction"))
            destination = &config.drag_friction;
        else if (sv_eq_cstr(key, "scale_friction"))
            destination = &config.scale_friction;
        else {
            fprintf(stderr, "Unknown configuration key: " SV_Fmt "\n",
                    SV_Arg(key));
            continue;
        }

        double parsed_value;

        if (!sv_to_double(value, &parsed_value)) {
            fprintf(stderr, "Invalid value for " SV_Fmt ": " SV_Fmt "\n",
                    SV_Arg(key), SV_Arg(value));
            continue;
        }

        *destination = parsed_value;
    }

    fclose(file);
    return config;
}

int generate_default_config(const char *filePath)
{
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        perror("fopen");
        return 0;
    }

    int result =
        fprintf(file,
                "min_scale = %.17g\n"
                "scroll_speed = %.17g\n"
                "drag_friction = %.17g\n"
                "scale_friction = %.17g\n",
                DEFAULT_CONFIG.min_scale, DEFAULT_CONFIG.scroll_speed,
                DEFAULT_CONFIG.drag_friction, DEFAULT_CONFIG.scale_friction);

    if (result < 0) {
        perror("fprintf");
        fclose(file);
        return 0;
    }

    if (fclose(file) == EOF) {
        perror("fclose");
        return 0;
    }

    return 1;
}
