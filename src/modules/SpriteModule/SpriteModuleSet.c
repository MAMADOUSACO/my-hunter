/*
** EPITECH PROJECT, 2025
** SpriteModule
** File description:
** Wrapper around CSFML sprite library.
*/

#include "./../../../include/SpriteModule.h"

void sfSprite_setScaleWindowBased(sprite_t *sprite,
    sfRenderWindow *window, sfVector2f scale)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2u texture_size = sfTexture_getSize(sprite->sf_texture);
    float x = (window_size.x * scale.x) / texture_size.x;
    float y = (window_size.y * scale.y) / texture_size.y;
    sfVector2f final_scale = {x, y};

    sprite->window_scale_theoretical = scale;
    sfSprite_setScale(sprite->sf_sprite, final_scale);
}