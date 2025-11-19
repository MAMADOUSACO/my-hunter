/*
** EPITECH PROJECT, 2025
** SpriteDrawModule
** File description:
** Dynamic array for efficient sprite rendering order management.
*/

#include "./../../../include/SpriteDrawModule.h"

static int resize_array(sprite_draw_array_t *array, int new_capacity)
{
    draw_entry_t *new_entries = safe_realloc(array->entries,
        sizeof(draw_entry_t) * new_capacity);

    if (new_entries == NULL)
        return EXIT_FAIL_DRAW;
    array->entries = new_entries;
    array->capacity = new_capacity;
    return EXIT_SUCC_DRAW;
}

static int find_sprite_index(sprite_draw_array_t *array, sfSprite *sprite)
{
    for (int i = 0; i < array->count; i++) {
        if (array->entries[i].sprite == sprite)
            return i;
    }
    return -1;
}

static int find_insert_position(sprite_draw_array_t *array, int draw_level)
{
    int i;

    for (i = 0; i < array->count; i++) {
        if (array->entries[i].draw_level > draw_level)
            return i;
    }
    return i;
}

sprite_draw_array_t *initialize_sprite_draw_array(void)
{
    sprite_draw_array_t *array = safe_malloc(sizeof(sprite_draw_array_t));

    if (array == NULL)
        return NULL;
    array->entries = safe_malloc(sizeof(draw_entry_t) *
        DRAW_ARRAY_INITIAL_CAPACITY);
    if (array->entries == NULL) {
        free(array);
        return NULL;
    }
    array->count = 0;
    array->capacity = DRAW_ARRAY_INITIAL_CAPACITY;
    return array;
}

void free_sprite_draw_array(sprite_draw_array_t *array)
{
    if (array == NULL)
        return;
    if (array->entries != NULL)
        free(array->entries);
    free(array);
}

int add_sprite_to_draw(sprite_draw_array_t *array, sfSprite *sprite,
    int draw_level)
{
    int insert_pos;
    int i;

    if (array == NULL || sprite == NULL)
        return EXIT_FAIL_DRAW;
    if (find_sprite_index(array, sprite) != -1)
        return EXIT_FAIL_DRAW;
    if (array->count >= array->capacity) {
        if (resize_array(array, array->capacity * 2) == EXIT_FAIL_DRAW)
            return EXIT_FAIL_DRAW;
    }
    insert_pos = find_insert_position(array, draw_level);
    for (i = array->count; i > insert_pos; i--) {
        array->entries[i] = array->entries[i - 1];
    }
    array->entries[insert_pos].sprite = sprite;
    array->entries[insert_pos].draw_level = draw_level;
    array->count++;
    return EXIT_SUCC_DRAW;
}

int remove_sprite_from_draw(sprite_draw_array_t *array, sfSprite *sprite)
{
    int index = find_sprite_index(array, sprite);
    int i;

    if (index == -1)
        return EXIT_FAIL_DRAW;
    for (i = index; i < array->count - 1; i++) {
        array->entries[i] = array->entries[i + 1];
    }
    array->count--;
    if (array->count > 0 && array->count < array->capacity / 4)
        resize_array(array, array->capacity / 2);
    return EXIT_SUCC_DRAW;
}

int update_draw_level(sprite_draw_array_t *array, sfSprite *sprite,
    int new_draw_level)
{
    if (remove_sprite_from_draw(array, sprite) == EXIT_FAIL_DRAW)
        return EXIT_FAIL_DRAW;
    return add_sprite_to_draw(array, sprite, new_draw_level);
}