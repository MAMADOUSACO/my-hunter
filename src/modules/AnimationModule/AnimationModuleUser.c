/*
** EPITECH PROJECT, 2025
** AnimationModule
** File description:
** Wrapper around CSFML sprite for easy animation.
*/

#include "./../../../include/AnimationModule.h"

int find_sprite_in_animation(animation_t *animation, sfSprite *sprite)
{
    int i;

    for (i = 0; i < animation->sprite_count; i++) {
        if (animation->animated_sprites[i]->sprite == sprite)
            return i;
    }
    return -1;
}

static void reset_sprite_animation(animated_sprite_t *anim_sprite, bool looping,
    void (*on_completed)(animated_sprite_t*))
{
    sfClock_restart(anim_sprite->clock);
    anim_sprite->time_offset = 0;
    anim_sprite->playing = true;
    anim_sprite->looping = looping;
    anim_sprite->current_frame = 0;
    anim_sprite->on_completed = on_completed;
}

animated_sprite_t *create_animated_sprite(sfSprite *sprite, bool looping,
    void (*on_completed)(animated_sprite_t*))
{
    animated_sprite_t *anim_sprite = safe_malloc(sizeof(animated_sprite_t));

    if (anim_sprite == NULL)
        return NULL;
    anim_sprite->sprite = sprite;
    anim_sprite->playing = true;
    anim_sprite->looping = looping;
    anim_sprite->clock = sfClock_create();
    anim_sprite->current_frame = 0;
    anim_sprite->time_offset = 0;
    anim_sprite->on_completed = on_completed;
    return anim_sprite;
}

int animation_play(animation_t *animation, sfSprite *sprite, bool looping,
    void (*on_completed)(animated_sprite_t*))
{
    int existing_index = find_sprite_in_animation(animation, sprite);
    animated_sprite_t *anim_sprite;

    if (existing_index != -1) {
        reset_sprite_animation(animation->animated_sprites[existing_index],
            looping, on_completed);
        return EXIT_SUCC_ANIM;
    }
    anim_sprite = create_animated_sprite(sprite, looping, on_completed);
    if (anim_sprite == NULL)
        return EXIT_FAIL_ANIM;
    sfSprite_setTextureRect(sprite, animation->frames[0]);
    return add_sprite_to_animation(animation, anim_sprite);
}

void set_frame(animated_sprite_t *sprite, animation_t *animation, int frame)
{
    float frame_duration;

    if (frame < 0 || frame >= animation->frame_count)
        return;
    frame_duration = animation->animation_duration / animation->frame_count;
    sfClock_restart(sprite->clock);
    sprite->time_offset = frame * frame_duration;
    sprite->current_frame = frame;
    sfSprite_setTextureRect(sprite->sprite, animation->frames[frame]);
}

static void handle_animation_complete(animation_t *animation,
    animated_sprite_t *anim_sprite, int index)
{
    if (anim_sprite->looping) {
        sfClock_restart(anim_sprite->clock);
        anim_sprite->time_offset = 0;
        anim_sprite->current_frame = 0;
        sfSprite_setTextureRect(anim_sprite->sprite, animation->frames[0]);
        return;
    }
    anim_sprite->playing = false;
    if (anim_sprite->on_completed != NULL)
        anim_sprite->on_completed(anim_sprite);
    remove_sprite_at_index(animation, index);
}

static void update_sprite_frame(animation_t *animation,
    animated_sprite_t *anim_sprite)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(anim_sprite->clock))
        + anim_sprite->time_offset;
    float progress = elapsed / animation->animation_duration;
    int new_frame = (int)(progress * animation->frame_count);

    if (new_frame >= animation->frame_count)
        new_frame -= 1;
    if (new_frame != anim_sprite->current_frame) {
        anim_sprite->current_frame = new_frame;
        sfSprite_setTextureRect(anim_sprite->sprite,
            animation->frames[new_frame]);
    }
}

static void update_single_sprite(animation_t *animation,
    animated_sprite_t *anim_sprite, int index)
{
    float elapsed;

    if (!anim_sprite->playing)
        return;
    elapsed = sfTime_asSeconds(sfClock_getElapsedTime(anim_sprite->clock)) +
        anim_sprite->time_offset;
    if (elapsed >= animation->animation_duration) {
        handle_animation_complete(animation, anim_sprite, index);
        return;
    }
    update_sprite_frame(animation, anim_sprite);
}

static void update_single_animation(animation_t *animation)
{
    int i;

    for (i = animation->sprite_count - 1; i >= 0; i--)
        update_single_sprite(animation, animation->animated_sprites[i], i);
}

void animation_update(animation_t *animations)
{
    animation_t *current = animations;

    while (current != NULL) {
        if (current->name != NULL)
            update_single_animation(current);
        current = current->next;
    }
}