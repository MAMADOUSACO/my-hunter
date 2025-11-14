/*
** EPITECH PROJECT, 2025
** SpriteModule
** File description:
** Wrapper around CSFML sprite library.
*/

#include "./../../../include/SpriteModule.h"

int ntm = 0;

void sfSprite_applyAspectRatio(sprite_t *sprite, sfRenderWindow *window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2f scale = sfSprite_getScale(sprite->sf_sprite);
    sfVector2u text = sfTexture_getSize(sprite->sf_texture);

    scale.x = scale.y * sprite->aspect_ratio;
    sfSprite_setScale(sprite->sf_sprite, scale);
    ntm++;
    if (ntm % 1000 != 0)
        return;
    my_printf("ar is %d, scale is %d %d\n", (int)sprite->aspect_ratio, (int)(scale.x*1000), (int)(scale.y*1000));
    my_printf("texture size is %d %d\n", text.x, text.y);
}

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