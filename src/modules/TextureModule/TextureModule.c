/*
** EPITECH PROJECT, 2025
** TextureModule
** File description:
** Wrapper around CSFML texture library for caching.
*/

#include "./../../../include/TextureModule.h"

static texture_t *create_texture_node(const char *texture_path)
{
    texture_t *new_texture = safe_malloc(sizeof(texture_t));
    sfTexture *sf_texture = sfTexture_createFromFile(texture_path, NULL);

    if (new_texture == NULL || sf_texture == NULL) {
        if (new_texture != NULL)
            free(new_texture);
        if (sf_texture != NULL)
            sfTexture_destroy(sf_texture);
        return NULL;
    }
    new_texture->texture_path = (char *)texture_path;
    new_texture->texture = sf_texture;
    new_texture->sprites_using = 1;
    new_texture->next = NULL;
    return new_texture;
}

static texture_t *find_texture(texture_t *textures, const char *texture_path)
{
    while (textures != NULL) {
        if (textures->texture_path != NULL &&
            str_cmp(textures->texture_path, texture_path) == 0)
            return textures;
        textures = textures->next;
    }
    return NULL;
}

static void add_texture_node(texture_t *textures, texture_t *new_texture)
{
    while (textures->next != NULL) {
        textures = textures->next;
    }
    textures->next = new_texture;
}

sfTexture *get_texture(texture_t *textures, const char *texture_path)
{
    texture_t *existing = find_texture(textures, texture_path);
    texture_t *new_texture;

    if (existing != NULL) {
        existing->sprites_using++;
        return existing->texture;
    }
    new_texture = create_texture_node(texture_path);
    if (new_texture == NULL)
        return NULL;
    add_texture_node(textures, new_texture);
    return new_texture->texture;
}

texture_t *initialize_texture_module(void)
{
    texture_t *head = safe_malloc(sizeof(texture_t));

    if (head == NULL)
        return NULL;
    head->texture_path = NULL;
    head->texture = NULL;
    head->sprites_using = 0;
    head->next = NULL;
    return head;
}

void free_texture_module(texture_t *textures)
{
    texture_t *temp;

    while (textures != NULL) {
        temp = textures;
        if (temp->texture != NULL)
            sfTexture_destroy(temp->texture);
        textures = textures->next;
        free(temp);
    }
}