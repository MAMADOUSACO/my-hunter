/*
** EPITECH PROJECT, 2025
** EventModule
** File description:
** Module to manage event processing.
*/

#include "./../../../include/EventModule.h"

int add_event(event_t *head, int (*callback)(sfEvent *event), char *cb_name)
{
    event_t *new_event = malloc(sizeof(event_t));

    if (new_event == NULL)
        return EXIT_FAIL_EVT;
    while (head->next != NULL) {
        if (str_cmp(cb_name, head->name) == 0)
            return ERROR_EVT_NAME_TAKEN;
        head = head->next;
    }
    new_event->name = cb_name;
    new_event->callback = callback;
    new_event->next = NULL;
    head->next = new_event;
    return EXIT_SUCC_EVT;
}

int remove_event(event_t *head, const char *restrict callback_name)
{
    event_t *temp;
    bool found_event = false;

    while (head != NULL) {
        if (str_cmp(head->name, callback_name) == 0)
            found_event = true;
        if (found_event)
            break;
        head = head->next;
    }
    if (!found_event)
        return ERROR_EVT_EVENT_MISSING;
    temp = head->next->next;
    free(head->next);
    head->next = temp;
    return EXIT_SUCC_EVT;
}

int execute_event_callbacks(event_t *head, sfEvent *event)
{
    while (head != NULL) {
        if (str_cmp(head->name, DEFAULT_NODE_NAME) != 0 &&
            head->callback(event) == EXIT_FAIL_EVT) {
            my_printf("A callback failed : %s\n", head->name);
            return EXIT_FAIL_EVT;
        }
        head = head->next;
    }
    return EXIT_SUCC_EVT;
}

event_t **initialize_array(void)
{
    event_t **array = malloc(sizeof(event_t*) * (EVENT_AMOUNT + 1));

    if (array == NULL)
        return NULL;
    array[EVENT_AMOUNT] = NULL;
    for (int i = 0; i < EVENT_AMOUNT; i++) {
        array[i] = malloc(sizeof(event_t));
        array[i]->name = DEFAULT_NODE_NAME;
        array[i]->callback = NULL;
        array[i]->next = NULL;
    }
    return array;
}

int free_array(event_t **array)
{
    event_t *temp;
    event_t *head;

    for (int i = 0; i < EVENT_AMOUNT; i++) {
        head = array[i];
        while (head != NULL) {
            temp = head;
            head = head->next;
            free(temp);
        }
    }
    free(array);
    return EXIT_SUCC_EVT;
}
