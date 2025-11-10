/*
** EPITECH PROJECT, 2025
** my_hunter
** File description:
** MyHunter header.
*/

#ifndef MY_HUNTER_H
    #define MY_HUNTER_H

    // INCLUDES

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <stdarg.h>
    #include <unistd.h>

    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>

    #include "./EventModule.h"

    // MACROS

    #define EXIT_SUCCESS 0
    #define EXIT_FAILURE 84
    #define EVENT_AMOUNT 13

// ENUMS

enum CURRENT_WINDOW {
    MENU = 1,
    SETTINGS = 2,
    GAME = 3,
};

// LIB FUNCTIONS

/// STR lIB
int str_cmp(const char *str1, const char *str2);

/// DEBUG LIB
int my_printf(const char *format, ...);

#endif