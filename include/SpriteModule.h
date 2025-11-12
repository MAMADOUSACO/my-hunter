/*
** EPITECH PROJECT, 2025
** SpriteModule
** File description:
** Sprite Module Header.
*/

#ifndef SPRITE_MODULE_H
    #define SPRITE_MODULE_H

    #include <SFML/System/Vector2.h>
    #include <SFML/Graphics/Color.h>
    #include <SFML/Graphics/Types.h>

typedef struct sprite_ini
{
    char *texture_path;
    float aspect_ratio;

    sfVector2u position_offset;
    sfVector2f position_scale;

    sfVector2u size_offset;
    sfVector2i size_scale;

    float rotation;
    sfColor color;
} sprite_ini_t;

typedef struct sprite
{
    int id;
    char *name;
    char *texture_path;

    sfSprite *sprite;
    sfTexture *texture;

    float aspect_ratio;
} sprite_t;

#endif
