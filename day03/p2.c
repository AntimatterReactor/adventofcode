/*
    This program acts as a solution to all the parts of day 10, AoC 2023
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

#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

#define GRID_SIZE 140
#define GRID_PADDING 2

char grid[GRID_SIZE + GRID_PADDING][GRID_SIZE + GRID_PADDING] = {{0}};

uint_fast32_t traverse_get_number (const size_t v, size_t h)
{
    uint_fast32_t r = 0;
    while (isdigit(grid[v][++h]));
    for (uint_fast32_t e = 1; isdigit(grid[v][--h]); e *= 10)
    {
        r += (grid[v][h] - '0') * e;
    }
    return r;
}

uint_fast32_t get_ratio (size_t v, size_t h)
{
    uint_fast32_t result = 1;
    int encounter = 0;

    if (isdigit(grid[v][h-1]))
        result *= traverse_get_number(v, h-1), ++encounter;
    if (isdigit(grid[v][h+1]))
        result *= traverse_get_number(v, h+1), ++encounter;
    if (encounter == 2)
        return result;
    
#define MATCH(C, x, y, z) (((bool)isdigit(C[x]) << 2) + ((bool)isdigit(C[y]) << 1) + (bool)isdigit(C[z]))

    switch (MATCH(grid[v-1], h-1, h, h+1)) {
    case 4:
    case 6:
        result *= traverse_get_number(v-1, h-1);
        break;
    case 1:
    case 3:
    case 7:
        result *= traverse_get_number(v-1, h+1);
        break;
    case 5:
        result *= traverse_get_number(v-1, h-1);
        result *= traverse_get_number(v-1, h+1);
        return result;
    case 2:
        result *= (grid[v-1][h] - '0');
        break;
    default:
        --encounter;
    }
    
    switch (MATCH(grid[v+1], h-1, h, h+1)) {
    case 4:
    case 6:
        result *= traverse_get_number(v+1, h-1);
        break;
    case 1:
    case 3:
    case 7:
        result *= traverse_get_number(v+1, h+1);
        break;
    case 5:
        result *= traverse_get_number(v+1, h-1);
        result *= traverse_get_number(v+1, h+1);
        return result;
    case 2:
        result *= (grid[v+1][h] - '0');
        break;
    default:
        --encounter;
    }

    if (encounter < 0)
        return 0;
    return result;
}

uint_fast32_t process_grid (void)
{
    uint_fast32_t sum = 0;
    for (size_t i = 1; i < GRID_SIZE + 1; ++i)
        for (size_t j = 1; j < GRID_SIZE + 1; ++j)
            if (grid[i][j] == '*')
                sum += get_ratio(i, j);
    return sum;
}

int main (void)
{
    char str[GRID_SIZE + GRID_PADDING] = {""};
    FILE* fp = fopen("input.txt", "r");
    for (size_t i = 0; fgets(str, sizeof(str), fp) != NULL; ++i)
        memcpy(grid[i + 1] + 1, str, GRID_SIZE);

    fclose(fp);
    
    printf("%lu\n", process_grid());
    return EXIT_SUCCESS;
}
