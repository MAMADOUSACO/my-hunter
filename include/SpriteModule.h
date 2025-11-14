/*
** EPITECH PROJECT, 2025
** SpriteModule
** File description:
** Sprite Module Header.
*/

#ifndef SPRITE_MODULE_H
    #define SPRITE_MODULE_H

    #include <stdlib.h>
    #include <stdbool.h>

    #include <SFML/System/Vector2.h>
    #include <SFML/Graphics.h>

    #define EXIT_SUCC_SPT 0
    #define EXIT_FAIL_SPT 84

    #define DEFAULT_ID_SPT -1

// TYPEDEF

typedef struct sprite_ini {
    char *texture_path;

    float aspect_ratio;
    sfVector2f min_screen_scale;
    sfVector2f max_screen_scale;

    sfVector2f position_scale;
    sfVector2f size_scale;

    float rotation;
    sfColor *color;
} sprite_ini_t;

typedef struct sprite {
    int id;
    char *name;
    char *texture_path;
    bool is_drawn;

    sfSprite *sf_sprite;
    sfTexture *sf_texture;

    float aspect_ratio;
    sfVector2f window_scale_theoretical;
    sfVector2f window_scale_real;
    sfVector2f min_screen_scale;
    sfVector2f max_screen_scale;

    struct sprite *next;
} sprite_t;

typedef struct sprite_creation {
    sprite_t *sprite;
    sfTexture *sf_texture;
    sfSprite *sf_sprite;
} sprite_creation_t;

// DEPENDENCIES
int my_printf(const char *format, ...);
int str_cmp(const char *str1, const char *str2);
void *safe_malloc(size_t bytes);

// MAIN FUNCTIONS
sprite_t *create_sprite(sprite_t *sprites, sprite_ini_t *data, char *name);
int destroy_sprite(sprite_t *sprites, int id);
sprite_t *initialize_sprite_module(void);
void free_sprite_module(sprite_t *sprites);

// DATA FUNCTIONS
sprite_ini_t *initialize_sprite_data(void);
void free_sprite_data(sprite_ini_t *data);

// GET FUNCTIONS
sprite_t *get_sprite_by_id(sprite_t *sprites, int id);
sprite_t *get_all_sprites_by_name(sprite_t *sprites, char *name);

// SET FUNCTIONS
void sfSprite_setScaleWindowBased(sprite_t *sprite,
    sfRenderWindow *window, sfVector2f scale);
void sfSprite_applyAspectRatio(sprite_t *sprite);

// DEBUG FUNCTIONS
void print_sprite_data(sprite_t *sprite);
void print_sprite_linked_list(sprite_t *sprites);

#endif
