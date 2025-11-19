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
    sfIntRect rect = sfSprite_getTextureRect(sprite->sf_sprite);
    my_printf("%d and %d\n", rect.width, rect.height);
    float x = (window_size.x * scale.x) / rect.width;
    float y = (window_size.y * scale.y) / rect.height;
    sfVector2f final_scale = {x, y};

    sprite->window_scale_theoretical = scale;
    sfSprite_setScale(sprite->sf_sprite, final_scale);
}