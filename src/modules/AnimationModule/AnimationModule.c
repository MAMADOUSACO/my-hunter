/*
** EPITECH PROJECT, 2025
** AnimationModule
** File description:
** Wrapper around CSFML sprite for easy animation.
*/

#include "./../../../include/AnimationModule.h"

static void calculate_single_frame(animation_t *animation, int i,
    sfVector2u texture_size)
{
    float col = i % animation->per_line;
    float row = i / animation->per_line;
    float frame_width = (float)texture_size.x / animation->per_line;
    float frame_height = (float)texture_size.y / animation->line_amount;

    animation->frames[i].left = (int)(col * frame_width);
    animation->frames[i].top = (int)(row * frame_height);
    animation->frames[i].width = (int)frame_width;
    animation->frames[i].height = (int)frame_height;
}

void calculate_rectangles(animation_t *animation)
{
    sfVector2u texture_size = sfTexture_getSize(animation->texture);
    int i;

    if (animation->frames != NULL)
        free(animation->frames);
    animation->frames = safe_malloc(sizeof(sfIntRect) * animation->frame_count);
    for (i = 0; i < animation->frame_count; i++)
        calculate_single_frame(animation, i, texture_size);
}

animation_t *initialize_animation_module(void)
{
    animation_t *head = safe_malloc(sizeof(animation_t));

    if (head == NULL)
        return NULL;
    head->name = NULL;
    head->texture = NULL;
    head->frames = NULL;
    head->frame_count = 0;
    head->animation_duration = 0;
    head->animated_sprites = NULL;
    head->sprite_count = 0;
    head->sprite_capacity = 0;
    head->next = NULL;
    return head;
}

static int check_duplicate_name(animation_t *animations, const char *name)
{
    animation_t *current = animations;

    while (current->next != NULL) {
        if (current->name != NULL && str_cmp(current->name, name) == 0)
            return 1;
        current = current->next;
    }
    return 0;
}

static void init_new_animation(animation_t *anim, animation_ini_t *ini_data)
{
    anim->name = ini_data->name;
    anim->texture = ini_data->texture;
    anim->frame_count = ini_data->frame_amount;
    anim->animation_duration = ini_data->animation_duration;
    anim->per_line = ini_data->per_line;
    anim->line_amount = ini_data->line_amount;
    anim->frames = NULL;
    anim->sprite_count = 0;
    anim->sprite_capacity = INITIAL_SPRITE_CAPACITY;
    anim->next = NULL;
}

animation_t *add_animation(animation_t *animations, animation_ini_t *ini_data)
{
    animation_t *new_anim = safe_malloc(sizeof(animation_t));
    animation_t *current = animations;

    if (new_anim == NULL || check_duplicate_name(animations, ini_data->name))
        return NULL;
    while (current->next != NULL)
        current = current->next;
    init_new_animation(new_anim, ini_data);
    new_anim->animated_sprites = safe_malloc(sizeof(animated_sprite_t*) *
        INITIAL_SPRITE_CAPACITY);
    calculate_rectangles(new_anim);
    current->next = new_anim;
    return new_anim;
}

static void cleanup_animation_sprites(animation_t *animation)
{
    int i;

    for (i = 0; i < animation->sprite_count; i++) {
        sfClock_destroy(animation->animated_sprites[i]->clock);
        free(animation->animated_sprites[i]);
    }
    if (animation->animated_sprites != NULL)
        free(animation->animated_sprites);
}

static void cleanup_animation(animation_t *animation)
{
    if (animation->frames != NULL)
        free(animation->frames);
    cleanup_animation_sprites(animation);
    free(animation);
}

int remove_animation(animation_t *animations, const char *name)
{
    animation_t *current = animations;
    animation_t *temp;

    while (current->next != NULL) {
        if (str_cmp(current->next->name, name) == 0) {
            temp = current->next;
            current->next = temp->next;
            cleanup_animation(temp);
            return EXIT_SUCC_ANIM;
        }
        current = current->next;
    }
    return EXIT_FAIL_ANIM;
}

void free_animation_module(animation_t *animations)
{
    animation_t *current = animations;
    animation_t *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        if (temp->name != NULL)
            cleanup_animation_sprites(temp);
        if (temp->frames != NULL)
            free(temp->frames);
        free(temp);
    }
}