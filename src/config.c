#include "string_view.h"
#include <stdio.h>

typedef struct {
    double min_scale;
    double scroll_speed;
    double drag_friction;
    double scale_friction;
} Config;

const Config defaultConfig = {
    .min_scale = 0.01,
    .scroll_speed = 1.5,
    .drag_friction = 6.0,
    .scale_friction = 4.0,
};

Config loadConfig(const char *filePath)
{
    Config config = defaultConfig;

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
    }

    fclose(file);
    return config;
}

int main(void)
{
    printf("Hello\n");
    return 0;
}

/* int main(void) { */
/*   // Just to test each function when first I add them. */
/*   String_View s = sv("    Hello, World   "); */
/*   sv_trim(&s); */
/*   printf("%.*s\n", s.len, s.data); */
/*   return 0; */
/* } */
