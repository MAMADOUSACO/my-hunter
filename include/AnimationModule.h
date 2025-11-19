/*
** EPITECH PROJECT, 2025
** AnimationModule
** File description:
** Animation Module Header.
*/

#ifndef ANIMATION_MODULE_H
    #define ANIMATION_MODULE_H

    #include <stdlib.h>
    #include <stdbool.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>

    #define EXIT_SUCC_ANIM 0
    #define EXIT_FAIL_ANIM 84
    #define INITIAL_SPRITE_CAPACITY 8

typedef struct animated_sprite {
    sfSprite *sprite;
    bool playing;
    bool looping;
    sfClock *clock;
    int current_frame;
    float time_offset;
    void (*on_completed)(struct animated_sprite *sprite);
} animated_sprite_t;

typedef struct animation {
    char *name;
    sfTexture *texture;
    sfIntRect *frames;
    int frame_count;
    float animation_duration;
    int per_line;
    int line_amount;
    animated_sprite_t **animated_sprites;
    int sprite_count;
    int sprite_capacity;
    struct animation *next;
} animation_t;

typedef struct animation_ini {
    sfTexture *texture;
    char *name;
    int frame_amount;
    int per_line;
    int line_amount;
    float animation_duration;
} animation_ini_t;

// DEPENDENCIES
int str_cmp(const char *str1, const char *str2);
void *safe_malloc(size_t bytes);
void *safe_realloc(void *ptr, size_t new_size);

// ANIMATION MODULE FUNCTIONS
animation_t *initialize_animation_module(void);
void free_animation_module(animation_t *animations);
animation_t *add_animation(animation_t *animations, animation_ini_t *ini_data);
int remove_animation(animation_t *animations, const char *name);
void calculate_rectangles(animation_t *animation);

// INTERNAL FUNCTIONS
int resize_sprite_array(animation_t *animation, int new_capacity);
int add_sprite_to_animation(animation_t *animation, animated_sprite_t *sprite);
int remove_sprite_at_index(animation_t *animation, int index);

// USER FUNCTIONS
int animation_play(animation_t *animation, sfSprite *sprite, bool looping,
    void (*on_completed)(animated_sprite_t*));
void animation_update(animation_t *animations);
void set_frame(animated_sprite_t *sprite, animation_t *animation, int frame);

// GET FUNCTIONS
animation_t *get_animation_by_name(animation_t *animations, const char *name);
animated_sprite_t **get_animation_sprites(animation_t *animation, int *count);

#endif