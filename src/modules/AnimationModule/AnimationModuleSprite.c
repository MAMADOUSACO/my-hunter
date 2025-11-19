/*
** EPITECH PROJECT, 2025
** AnimationModule
** File description:
** Wrapper around CSFML sprite for easy animation.
*/

#include "./../../../include/AnimationModule.h"

int resize_sprite_array(animation_t *animation, int new_capacity)
{
    animated_sprite_t **new_array = safe_realloc(animation->animated_sprites,
        sizeof(animated_sprite_t*) * new_capacity);

    if (new_array == NULL)
        return EXIT_FAIL_ANIM;
    animation->animated_sprites = new_array;
    animation->sprite_capacity = new_capacity;
    return EXIT_SUCC_ANIM;
}

int add_sprite_to_animation(animation_t *animation, animated_sprite_t *sprite)
{
    if (animation->sprite_count >= animation->sprite_capacity) {
        if (resize_sprite_array(animation,
            animation->sprite_capacity * 2) == EXIT_FAIL_ANIM)
            return EXIT_FAIL_ANIM;
    }
    animation->animated_sprites[animation->sprite_count] = sprite;
    animation->sprite_count++;
    return EXIT_SUCC_ANIM;
}

int remove_sprite_at_index(animation_t *animation, int index)
{
    if (index < 0 || index >= animation->sprite_count)
        return EXIT_FAIL_ANIM;
    sfClock_destroy(animation->animated_sprites[index]->clock);
    free(animation->animated_sprites[index]);
    for (int i = index; i < animation->sprite_count - 1; i++)
        animation->animated_sprites[i] = animation->animated_sprites[i + 1];
    animation->sprite_count--;
    if (animation->sprite_count > 0 &&
        animation->sprite_count < animation->sprite_capacity / 4)
        resize_sprite_array(animation, animation->sprite_capacity / 2);
    return EXIT_SUCC_ANIM;
}