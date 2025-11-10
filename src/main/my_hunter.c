/*
** EPITECH PROJECT, 2025
** my_hunter
** File description:
** Main file that starts everything.
*/

#include "./../../include/MyHunter.h"

int window_loop(sfRenderWindow *window, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(window);
    }
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_display(window);
    return EXIT_SUCCESS;
}

int main(void)
{
    enum CURRENT_WINDOW Context = MENU;
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode,
        "SFML window", sfResize | sfClose, NULL);
    sfEvent event;

    if (!window)
        return EXIT_FAILURE;
    while (sfRenderWindow_isOpen(window)) {
        if (window_loop(window, &event) == EXIT_FAILURE)
            break;
    }
    sfRenderWindow_destroy(window);
    return EXIT_SUCCESS;
}