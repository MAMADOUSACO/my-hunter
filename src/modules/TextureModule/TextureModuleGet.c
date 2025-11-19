/*
** EPITECH PROJECT, 2025
** TextureModule
** File description:
** Wrapper around CSFML texture library for caching.
*/

#include "./../../../include/TextureModule.h"

int get_texture_usage_count(texture_t *textures, const char *texture_path)
{
    texture_t *found = get_texture(textures, texture_path);

    if (found == NULL)
        return 0;
    return found->sprites_using;
}