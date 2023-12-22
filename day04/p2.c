/*
    This program acts as a solution to day 4, part 2 of 2023's Advent of Code
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

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define NUMBERS_TABLE_SIZE 100
#define CARDS_RANGE 202

struct CardsType {
    unsigned amount;
    bool winnumbers[NUMBERS_TABLE_SIZE];
    bool ordnumbers[NUMBERS_TABLE_SIZE];
} table[CARDS_RANGE] = {{0}, {0}, {0}};

unsigned get_cards(const unsigned id)
{
    unsigned r = 0;
    for (unsigned i = 0; i < NUMBERS_TABLE_SIZE; ++i)
        if (table[id].winnumbers[i] && table[id].ordnumbers[i])
            table[id + (++r)].amount += 1 * table[id].amount;

    return table[id].amount;
}

unsigned process_line(const char *ss, const unsigned vp)
{
    for (unsigned x = 0, i = 0; i < 10; ++i)
    {
        while (isspace(*ss)) ++ss;
        sscanf(ss, "%u", &x);
        while (!isspace(*ss)) ++ss;
        assert(x < NUMBERS_TABLE_SIZE);
        table[vp].winnumbers[x] = 1;
    }

    while (*ss != '|') ++ss;
    ++ss;

    for (unsigned x = 0, i = 0; i < 25; i++)
    {
        while (isspace(*ss)) ++ss;
        sscanf(ss, "%u", &x);
        while (!isspace(*ss)) ++ss;
        assert(x < NUMBERS_TABLE_SIZE);
        table[vp].ordnumbers[x] = 1;
    }
    
    return 1;
}

int main(void)
{
    char str[128] = {""};
    unsigned total = 0;
    FILE* fp = fopen("input.txt", "r");
    for (unsigned i = 0; fgets(str, sizeof(str), fp) != NULL; ++i)
        table[i].amount = process_line(strchr(str, ':') + 1, i);
    fclose(fp);
    for (unsigned i = 0; i < CARDS_RANGE; ++i)
        total += get_cards(i);
    printf("%u\n", total);
    return EXIT_SUCCESS;
}
