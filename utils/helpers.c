//
// Created by Mykyta Maliarenko on 14.05.2020.
//

#include "helpers.h"
#include <stdlib.h>


/**
 * @brief Parse int to string.
 *
 * @param val value to parse.
 * @param error if not null result of operations will be written here.
 */
int parseInt(const char* val, bool* error)
{
    int res;
    char* end;

    res = strtol(val, &end, 0);
    if (error != NULL)
    {
        if (*end == '\0')
            *error = false;
        else
            *error = true;
    }

    return res;
}