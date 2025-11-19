/*
** EPITECH PROJECT, 2025
** AnimationModule
** File description:
** Wrapper around CSFML sprite for easy animation.
*/

#include "./../../../include/AnimationModule.h"

animation_t *get_animation_by_name(animation_t *animations, const char *name)
{
    while (animations != NULL) {
        if (animations->name != NULL && str_cmp(animations->name, name) == 0)
            return animations;
        animations = animations->next;
    }
    return NULL;
}

animated_sprite_t **get_animation_sprites(animation_t *animation, int *count)
{
    if (animation == NULL) {
        if (count != NULL)
            *count = 0;
        return NULL;
    }
    if (count != NULL)
        *count = animation->sprite_count;
    return animation->animated_sprites;
}