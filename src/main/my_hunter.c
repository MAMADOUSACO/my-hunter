/*
** EPITECH PROJECT, 2025
** my_hunter
** File description:
** Main file that starts everything.
*/

#include "./../../include/MyHunter.h"
#include "./../../include/EventModule.h"
#include "./../../include/SpriteModule.h"

int window_loop(sfRenderWindow *window, sfEvent *event, event_t **event_array)
{
    sfRenderWindow_clear(window, sfBlack);
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(window);
        execute_event_callbacks(event_array[event->type], event);
    }
    sfRenderWindow_display(window);
    return EXIT_SUCC;
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

    sprite_ini_t *data = initialize_sprite_data();
    data->texture_path = "./assets/images/backgrounds/traumatisme.png";
    sprite_t *my_sprite = create_sprite(sprite_array, data, "my_sprite");

    free_sprite_data(data);
    destroy_sprite(sprite_array, 0);

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
    sfSprite_setScale(sprite, vector);*/

    if (!window)
        return EXIT_FAIL;
    while (sfRenderWindow_isOpen(window)) {
        if (window_loop(window, &event, event_array) == EXIT_FAIL)
            break;
    }
    sfRenderWindow_destroy(window);
    free_event_module(event_array);
    free_sprite_module(sprite_array);
    return EXIT_SUCC;
}
