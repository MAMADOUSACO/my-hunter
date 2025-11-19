/*
** EPITECH PROJECT, 2025
** safe_realloc
** File description:
** A wrapper around realloc for retry logic.
*/

#include <stdlib.h>
#include <unistd.h>

void *safe_realloc(void *ptr, size_t new_size)
{
    void *reallocated = NULL;

    for (int i = 0; i < 10; i++) {
        reallocated = realloc(ptr, new_size);
        if (reallocated != NULL)
            return reallocated;
        write(2, "Realloc failed! Retrying...\n", 28);
    }
    write(2, "A realloc completely failed!\n", 29);
    return NULL;
}