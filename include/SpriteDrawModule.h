/*
** EPITECH PROJECT, 2025
** SpriteDrawModule
** File description:
** Dynamic array for efficient sprite rendering order management.
*/

#ifndef SPRITE_DRAW_MODULE_H
    #define SPRITE_DRAW_MODULE_H

    #include <SFML/Graphics.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #define EXIT_SUCC_DRAW 0
    #define EXIT_FAIL_DRAW 84
    
    #define DRAW_ARRAY_INITIAL_CAPACITY 16

typedef struct draw_entry {
    sfSprite *sprite;
    int draw_level;
} draw_entry_t;

typedef struct sprite_draw_array {
    draw_entry_t *entries;
    int count;
    int capacity;
} sprite_draw_array_t;

// DEPENDENCIES
void *safe_malloc(size_t bytes);
void *safe_realloc(void *ptr, size_t new_size);

// DRAW ARRAY FUNCTIONS
sprite_draw_array_t *initialize_sprite_draw_array(void);
void free_sprite_draw_array(sprite_draw_array_t *array);
int add_sprite_to_draw(sprite_draw_array_t *array, sfSprite *sprite,
    int draw_level);
int remove_sprite_from_draw(sprite_draw_array_t *array, sfSprite *sprite);
int update_draw_level(sprite_draw_array_t *array, sfSprite *sprite,
    int new_draw_level);

// GET FUNCTIONS
int get_draw_count(sprite_draw_array_t *array);

#endif