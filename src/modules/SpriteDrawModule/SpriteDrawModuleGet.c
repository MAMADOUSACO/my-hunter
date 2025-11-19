/*
** EPITECH PROJECT, 2025
** SpriteDrawModule
** File description:
** Dynamic array for efficient sprite rendering order management.
*/

#include "./../../../include/SpriteDrawModule.h"

int get_draw_count(sprite_draw_array_t *array)
{
    if (array == NULL)
        return 0;
    return array->count;
}