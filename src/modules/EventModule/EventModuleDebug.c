/*
** EPITECH PROJECT, 2025
** EventModule
** File description:
** Module to debug event processing.
*/

#include "./../../../include/EventModule.h"

void print_array(event_t **array)
{
    my_printf("-- ARRAY BEGIN\n");
    for (int i = 0; i < EVENT_AMOUNT; i++) {
        my_printf("--- EVENT %d BEGIN\n", i);
        print_callbacks(array[i]);
        my_printf("--- EVENT %d END\n", i);
    }
    my_printf("-- ARRAY END\n");
}

void print_callbacks(event_t *head)
{
    for (int counter = 1; head != NULL; counter++) {
        my_printf("---- Callback print begin\n");
        my_printf("Callback n%d\n", counter);
        my_printf("Name : %s\n", head->name);
        my_printf("---- Callback print end\n");
        head = head->next;
    }
}
