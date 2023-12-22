/*
    This program acts as a solution to day 6, part 2 of 2023's Advent of Code
    Copyright (C) 2023 by Ezra Alvarion

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

uint_least64_t processline (const char*);
uint_least64_t processdata (const uint_least64_t, const uint_least64_t);

int main(void)
{
    char str[64] = {""};
    uint_least64_t time = 0, dist = 0;
    uint_least64_t result = 0;
    FILE* fp = fopen("input.txt", "r");

    fgets(str, sizeof(str), fp);
    time = processline(strchr(str, ':') + 1);

    fgets(str, sizeof(str), fp);
    dist = processline(strchr(str, ':') + 1); 

    fclose(fp);

    result = processdata(time, dist);

    printf("%lu\n", result);
    return EXIT_SUCCESS;
}

uint_least64_t reverse_numberll (uint_least64_t x) {
    uint_least64_t r = 0;
    while (x > 0)
    {
        r = (r * 10) + (x % 10);
        x /= 10;
    }
    return r;
}

uint_least64_t padding_numberll (uint_least64_t x, const uint_least64_t en) {
    while (en > x)
        x *= 10;
    return x;
}

uint_least64_t processline (const char* str)
{
    uint_least64_t en = 1, val = 0;
    for(; *str != '\n' && *str != '\0'; ++str)
    {
        if (isdigit(*str))
        {
            val += (*str - '0') * (en *= 10) / 10;
        }
    }
    return padding_numberll(reverse_numberll(val), en / 10);
}

uint_least64_t processdata (const uint_least64_t time, const uint_least64_t dist)
{
    uint_least64_t start = 0, end = 0;
    for (uint_least64_t j = 1; j < time; ++j)
    {
        if ((time - j) * j > dist)
        {
            start = j;
            break;
        }
    }
    for (uint_least64_t j = time; j > 0; --j)
    {
        if ((time - j) * j > dist)
        {
            end = j;
            break;
        }
    }
    return end - start + 1;
}
