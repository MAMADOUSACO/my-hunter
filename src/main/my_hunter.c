/*
** EPITECH PROJECT, 2025
** my_hunter
** File description:
** Main file that starts everything.
*/

#include "./../../include/MyHunter.h"
#include "./../../include/EventModule.h"
#include "./../../include/SpriteModule.h"
#include "./../../include/TextureModule.h"
#include "./../../include/SpriteDrawModule.h"

int window_loop(sfRenderWindow *window, sfEvent *event,
    event_t **event_array, sprite_draw_array_t *sprite_draw_array)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(window);
        execute_event_callbacks(event_array[event->type], event);
    }
    sfRenderWindow_clear(window, sfBlack);
    for (int i = 0; i < sprite_draw_array->count; i++) {
        sfRenderWindow_drawSprite(window, sprite_draw_array->entries[i].sprite, NULL);
    }
    sfRenderWindow_display(window);
    return EXIT_SUCC;
}

int mouse_clicked(sfEvent *event)
{
    my_printf("mouse was clicked coordinates are %d %d\n", event->mouseButton.x, event->mouseButton.y);
    return EXIT_SUCC_EVT;
}

int main(void)
{
    enum CURRENT_WINDOW Context = MENU;
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode,
        "SFML window", sfResize | sfClose, NULL);
    sfEvent event;

    // ini some stuff here
    event_t **event_array = initialize_event_module();
    sprite_t *sprite_array = initialize_sprite_module();
    texture_t *texture_array = initialize_texture_module();
    sprite_draw_array_t *sprite_draw_array = initialize_sprite_draw_array();

    // CREATING A SPRITE
    sprite_ini_t *data = initialize_sprite_data();
    if (data == NULL)
        my_printf("error data\n");
    data->texture_path = "./assets/images/backgrounds/traumatisme.png";
    sprite_t *my_sprite = create_sprite(sprite_array, data, "my_sprite", texture_array);
    sfVector2f test_scale = {1, 1};
    sfVector2f other_scale = {.2, .2};
    sprite_t *other_sprite = create_sprite(sprite_array, data, "other_sprite", texture_array);
    sfSprite_setScaleWindowBased(my_sprite, window, test_scale);
    sfSprite_setScaleWindowBased(other_sprite, window, other_scale);
    add_sprite_to_draw(sprite_draw_array, my_sprite->sf_sprite, 0);
    add_sprite_to_draw(sprite_draw_array, other_sprite->sf_sprite, 1);
    free_sprite_data(data);

    // EVENT
    add_event(event_array[sfEvtMouseButtonPressed], &mouse_clicked, "mouse_clicked");

    if (!window)
        return EXIT_FAIL;
    while (sfRenderWindow_isOpen(window)) {
        if (window_loop(window, &event, event_array, sprite_draw_array) == EXIT_FAIL)
            break;
    }
    sfRenderWindow_destroy(window);
    free_event_module(event_array);
    free_sprite_module(sprite_array);
    free_texture_module(texture_array);
    free_sprite_draw_array(sprite_draw_array);
    return EXIT_SUCC;
}

        //sfSprite_setScaleWindowBased(my_sprite, window, test_scale);
        //sfSprite_applyAspectRatio(my_sprite);

            /*sprite_ini_t *data = initialize_sprite_data();
    sprite_t *my_sprite = create_sprite(sprite_array, data, "my_sprite");
    sprite_t *my_sprite_2 = create_sprite(sprite_array, data, "my_sprite_2");
    sprite_t *my_sprite_3 = create_sprite(sprite_array, data, "my_sprite_3");
    print_sprite_linked_list(sprite_array);
    destroy_sprite(sprite_array, 0);
    my_printf("\n\n");
    print_sprite_linked_list(sprite_array);
    sprite_t *my_sprite4 = create_sprite(sprite_array, data, "my_sprite4");
    free_sprite_data(data);
    my_printf("\n\n");
    print_sprite_linked_list(sprite_array);/*/

    /*sfTexture *texture = sfTexture_createFromFile("./assets/images/backgrounds/traumatisme.png", NULL);
    sfSprite *sprite = sfSprite_create();
    sfVector2f vector = {0.265, 0.24};
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setScale(sprite, vector);
*/