/*
** EPITECH PROJECT, 2025
** SpriteModule
** File description:
** Wrapper around CSFML texture library for caching.
*/

#ifndef TEXTURE_MODULE_H
    #define TEXTURE_MODULE_H

    #include <stdlib.h>
    #include <stdbool.h>

    #include <SFML/System/Vector2.h>
    #include <SFML/Graphics.h>

    #define EXIT_SUCC_TXT 0
    #define EXIT_FAIL_TXT 84

// TYPEDEF

typedef struct texture {
    char *texture_path;
    sfTexture *texture;
    int sprites_using;
    struct texture *next;
} texture_t;

// DEPENDENCIES
int str_cmp(const char *str1, const char *str2);
void *safe_malloc(size_t bytes);

// MAIN FUNCTIONS
texture_t *initialize_texture_module(void);
sfTexture *get_texture(texture_t *textures, const char *texture_path);
void free_texture_module(texture_t *textures);
int get_texture_usage_count(texture_t *textures, const char *texture_path);

#endif