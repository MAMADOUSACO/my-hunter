/*
** EPITECH PROJECT, 2025
** SpriteModule
** File description:
** Wrapper around CSFML sprite library.
*/

#include "./../../../include/SpriteModule.h"

sprite_t *get_sprite_by_id(sprite_t *sprites, int id)
{
    while (sprites->id != id && sprites != NULL) {
        sprites = sprites->next;
    }
    if (sprites == NULL)
        return NULL;
    return sprites;
}
