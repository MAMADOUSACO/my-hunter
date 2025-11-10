/*
** EPITECH PROJECT, 2025
** my_hunter
** File description:
** Event Module Header.
*/

#ifndef EVENT_MODULE_H
    #define EVENT_MODULE_H

    #include <SFML/Graphics.h>

    #define ERROR_NAME_TAKEN -1
    #define ERROR_EVENT_NOT_FOUND -2

typedef struct event {
    char *name;
    int (*callback)(sfEvent *Event);
    struct event *next;
} event_t;

#endif