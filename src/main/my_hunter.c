/*
** EPITECH PROJECT, 2025
** my_hunter
** File description:
** Main file that starts everything.
*/

#include "./../../include/MyHunter.h"
#include "./../../include/EventModule.h"

int window_loop(sfRenderWindow *window, sfEvent *event, event_t **event_array)
{
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
    event_t **event_array = initialize_array();
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode,
        "SFML window", sfResize | sfClose, NULL);
    sfEvent event;

    sfTexture *texture = sfTexture_createFromFile("./assets/images/backgrounds/traumatisme.png", NULL);
    sfSprite *sprite = sfSprite_create();
    sfVector2f vector = {0.265, 0.24};
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setScale(sprite, vector);

    if (!window)
        return EXIT_FAIL;
    while (sfRenderWindow_isOpen(window)) {
        if (window_loop(window, &event, event_array) == EXIT_FAIL)
            break;
        sfRenderWindow_drawSprite(window, sprite, NULL);
    }
    sfRenderWindow_destroy(window);
    free_array(event_array);
    return EXIT_SUCC;
}
