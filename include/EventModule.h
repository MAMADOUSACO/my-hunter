/*
** EPITECH PROJECT, 2025
** EventModule
** File description:
** Event Module Header.
*/

#ifndef EVENT_MODULE_H
    #define EVENT_MODULE_H

    #include <SFML/Graphics.h>
    #include <stdbool.h>
    #include <stdlib.h>

    #define EXIT_SUCC_EVT 0
    #define EXIT_FAIL_EVT 84

    #define ERROR_EVT_NAME_TAKEN -1
    #define ERROR_EVT_EVENT_MISSING -2

    #define EVENT_AMOUNT 22
    #define DEFAULT_NODE_NAME "0"

typedef struct event {
    char *name;
    int (*callback)(sfEvent *Event);
    struct event *next;
} event_t;

// DEPENDENCIES
int my_printf(const char *format, ...);
int str_cmp(const char *str1, const char *str2);

// EVENT MODULE FUNCTIONS
event_t **initialize_array(void);
int free_array(event_t **array);
int execute_event_callbacks(event_t *head, sfEvent *event);
int add_event(event_t *head, int (*callback)(sfEvent *event), char *cb_name);
int remove_event(event_t *head, const char *restrict callback_name);

// EVENT MODULE DEBUG FUNCTIONS
void print_array(event_t **array);
void print_callbacks(event_t *head);

#endif
