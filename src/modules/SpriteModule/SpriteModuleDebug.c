/*
** EPITECH PROJECT, 2025
** SpriteModule
** File description:
** Wrapper around CSFML sprite library.
*/

#include "./../../../include/SpriteModule.h"

void print_sprite_data(sprite_t *sprite)
{
    int aspect_int = (int)sprite->aspect_ratio;
    int aspect_dec = (int)(sprite->aspect_ratio * 100 - aspect_int * 100);

    my_printf("---- PRINT SPRITE BEGIN\n");
    my_printf("Id : %d\n", sprite->id);
    my_printf("Name : %s\n", sprite->name);
    my_printf("Texture path : %s\n", sprite->texture_path);
    my_printf("Aspect ratio (to 1/100th) : %d.%d\n", aspect_int, aspect_dec);
    my_printf("---- PRINT SPRITE END\n");
}

void print_sprite_linked_list(sprite_t *sprites)
{
    while (sprites != NULL) {
        if (sprites->id != DEFAULT_ID_SPT)
            print_sprite_data(sprites);
        sprites = sprites->next;
    }
}
