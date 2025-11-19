/*
** EPITECH PROJECT, 2025
** SpriteModule
** File description:
** Wrapper around CSFML sprite library.
*/

#include "./../../../include/SpriteModule.h"

/*
Because we use a method of "expected id",
this implies sorting the linked list by ids in ascendant order.
(Example : Avoid duplicate id "2" in list 0,1,3,2)
*/
static int get_next_id(sprite_t *sprites)
{
    int expected_id = -1;

    while (sprites != NULL) {
        if (sprites->id != expected_id)
            return expected_id;
        expected_id++;
        sprites = sprites->next;
    }
    return expected_id;
}

static sprite_creation_t *create_sprite_elements(sprite_ini_t *ini_data, texture_t *textures)
{
    sprite_creation_t *data = safe_malloc(sizeof(sprite_creation_t));
    sprite_t *spr = safe_malloc(sizeof(sprite_t));
    sfTexture *sf_txt = get_texture(textures, ini_data->texture_path);
    sfSprite *sf_spr = sfSprite_create();

    if (data == NULL || spr == NULL || sf_txt == NULL || sf_spr == NULL) {
        if (data != NULL)
            free(data);
        if (spr != NULL)
            free(spr);
        if (sf_txt != NULL)
            free(sf_txt);
        if (sf_spr != NULL)
            free(sf_spr);
        return NULL;
    }
    data->sprite = spr;
    data->sf_texture = sf_txt;
    data->sf_sprite = sf_spr;
    return data;
}

static void place_sprite_in_array(sprite_t *sprites, sprite_t *sprite)
{
    while (sprites->id < (sprite->id - 1)) {
        sprites = sprites->next;
    }
    sprite->next = sprites->next;
    sprites->next = sprite;
}

static void initialize_sprite_properties(sprite_t *sprite,
    sprite_ini_t *ini_data)
{
    sfSprite_setPosition(sprite->sf_sprite, ini_data->position_scale);
    sfSprite_setRotation(sprite->sf_sprite, ini_data->rotation);
    sfSprite_setScale(sprite->sf_sprite, ini_data->size_scale);
    sfSprite_setColor(sprite->sf_sprite, *ini_data->color);
    sfSprite_setTexture(sprite->sf_sprite, sprite->sf_texture, sfTrue);
    // AJouter une propriété par rapport a la taille du rect ? nécessaire jpense
}

sprite_t *create_sprite(sprite_t *sprites, sprite_ini_t *ini_data,
    char *name, texture_t *textures)
{
    sprite_creation_t *creation_data = create_sprite_elements(ini_data, textures);
    sprite_t *sprite;

    if (creation_data == NULL)
        return NULL;
    sprite = creation_data->sprite;
    sprite->aspect_ratio = ini_data->aspect_ratio;
    sprite->id = get_next_id(sprites);
    sprite->name = name;
    sprite->texture_path = ini_data->texture_path;
    sprite->sf_texture = creation_data->sf_texture;
    sprite->sf_sprite = creation_data->sf_sprite;
    sprite->min_screen_scale = ini_data->min_screen_scale;
    sprite->max_screen_scale = ini_data->max_screen_scale;
    initialize_sprite_properties(sprite, ini_data);
    place_sprite_in_array(sprites, sprite);
    free(creation_data);
    return sprite;
}

int destroy_sprite(sprite_t *sprites, int id)
{
    sprite_t *temp;

    if (id == DEFAULT_ID_SPT)
        return EXIT_FAIL_SPT;
    while (sprites->next->id != id && sprites->next != NULL) {
        sprites = sprites->next;
    }
    if (sprites->next == NULL)
        return EXIT_FAIL_SPT;
    temp = sprites->next;
    sprites->next = sprites->next->next;
    sfSprite_destroy(temp->sf_sprite);
    free(temp);
    return EXIT_SUCC_SPT;
}

sprite_t *initialize_sprite_module(void)
{
    sprite_t *sprite = safe_malloc(sizeof(sprite_t));

    sprite->id = DEFAULT_ID_SPT;
    sprite->next = NULL;
    return sprite;
}

void free_sprite_module(sprite_t *sprites)
{
    sprite_t *temp = NULL;

    while (sprites != NULL) {
        temp = sprites;
        if (sprites->id != DEFAULT_ID_SPT) {
            sfSprite_destroy(temp->sf_sprite);
        }
        sprites = sprites->next;
        free(temp);
    }
}
