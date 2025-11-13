/*
** EPITECH PROJECT, 2025
** safe_malloc
** File description:
** A wrapper around malloc for retry logic.
*/

#include <stdlib.h>
#include <unistd.h>

// Standard 10 retries.
void *safe_malloc(size_t bytes)
{
    void *allocated = NULL;

    for (int i = 0; i < 10; i++) {
        allocated = malloc(bytes);
        if (allocated != NULL)
            return allocated;
        write(2, "Malloc failed! Retrying...\n", 27);
    }
    write(2, "A malloc completely failed!\n", 28);
    return NULL;
}
