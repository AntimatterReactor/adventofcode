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
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define GRID_SIZE 140
#define GRID_PADDING 2

char grid[GRID_SIZE + GRID_PADDING][GRID_SIZE + GRID_PADDING] = {{0}};

bool check_surroundings (const long v, const long h)
{
    bool r = false;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            r += grid[v+i][h+j] != '.' && ispunct(grid[v+i][h+j]);
    return r;
}

uint_fast32_t get_number (const size_t v, size_t h)
{
    uint_fast32_t r = 0;
    bool cond = false;
    do {
        cond += check_surroundings(v, h);
    } while (isdigit(grid[v][++h]));
    if (!cond)
        return 0;
    for (uint_fast32_t e = 1; isdigit(grid[v][--h]); e *= 10)
    {
        r += (grid[v][h] - '0') * e;
    }
    return r;
}


uint_fast32_t process_grid (void)
{
    uint_fast32_t sum = 0;
    bool pd = false;
    for (size_t i = 1; i < GRID_SIZE + 1; ++i)
    {
        for (size_t j = 1; j < GRID_SIZE + 1; ++j)
        {
            if (!pd && isdigit(grid[i][j]))
            {
                sum += get_number(i, j);
                pd = true;
            }
            else if (pd && !isdigit(grid[i][j])) {
                pd = false;
            }
        }
    }
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
