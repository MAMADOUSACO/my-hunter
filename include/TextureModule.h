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

    #define EXIT_SUCC_SPT 0
    #define EXIT_FAIL_SPT 84

    #define DEFAULT_ID_SPT -1

// TYPEDEF

typedef struct texture {
    char *texture_path;
    sfTexture *texture;
    int sprites_using;
    struct texture *next;
} texture_t;