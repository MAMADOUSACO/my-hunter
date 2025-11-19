/*
** EPITECH PROJECT, 2025
** safe_calloc
** File description:
** A wrapper around calloc for retry logic.
*/

#include <stdlib.h>
#include <unistd.h>

void *safe_calloc(size_t count, size_t size)
{
    void *allocated = NULL;

    for (int i = 0; i < 10; i++) {
        allocated = calloc(count, size);
        if (allocated != NULL)
            return allocated;
        write(2, "Calloc failed! Retrying...\n", 27);
    }
    write(2, "A calloc completely failed!\n", 28);
    return NULL;
}