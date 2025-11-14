/*
** EPITECH PROJECT, 2025
** SpriteModule
** File description:
** Wrapper around CSFML sprite library.
*/

#include "./../../../include/SpriteModule.h"

static sfColor *initialize_default_color(void)
{
    sfColor *color = safe_malloc(sizeof(sfColor));

    if (color == NULL)
        return NULL;
    color->a = 255;
    color->r = 255;
    color->g = 255;
    color->b = 255;
    return color;
}

sprite_ini_t *initialize_sprite_data(void)
{
    sprite_ini_t *data = safe_malloc(sizeof(sprite_ini_t));
    sfVector2f scale = {0.5, 0.5};
    sfVector2f min_scale = {0, 0};
    sfVector2f max_scale = {10, 10};

    if (data == NULL)
        return NULL;
    data->aspect_ratio = 1;
    data->color = initialize_default_color();
    data->position_scale = scale;
    data->min_screen_scale = min_scale;
    data->max_screen_scale = max_scale;
    data->size_scale = scale;
    data->rotation = 0;
    data->texture_path = "";
    if (data->color == NULL) {
        free(data);
        return NULL;
    }
    return data;
}

void free_sprite_data(sprite_ini_t *data)
{
    free(data->color);
    free(data);
}
