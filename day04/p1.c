/*
    This program acts as a solution to the day 4 part 1 of AoC 2023
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

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBERS_TABLE_SIZE 100

unsigned process_line(const char *ss)
{
    bool winnumbers[NUMBERS_TABLE_SIZE] = {0};
    bool ordnumbers[NUMBERS_TABLE_SIZE] = {0};

    for (unsigned x = 0, i = 0; i < 10; i++)
    {
        while (isspace(*ss)) ++ss;
        sscanf(ss, "%u", &x);
        while (!isspace(*ss)) ++ss;
        assert(x < NUMBERS_TABLE_SIZE);
        winnumbers[x] = 1;
    }

    while (*ss != '|') ++ss;
    ++ss;

    for (unsigned x = 0, i = 0; i < 25; i++)
    {
        while (isspace(*ss)) ++ss;
        sscanf(ss, "%u", &x);
        while (!isspace(*ss)) ++ss;
        assert(x < NUMBERS_TABLE_SIZE);
        ordnumbers[x] = 1;
    }
    
    unsigned t = 1;

    for (unsigned i = 0; i < NUMBERS_TABLE_SIZE; ++i)
        if (ordnumbers[i] && winnumbers[i])
            t <<= 1;

    return t >> 1;
}

int main(void)
{
    char str[128] = {""};
    unsigned total = 0;
    FILE* fp = fopen("input.txt", "r");
    while (fgets(str, sizeof(str), fp) != NULL)
        total += process_line(strchr(str, ':') + 1);
    fclose(fp);
    printf("%u\n", total);
    return EXIT_SUCCESS;
}
