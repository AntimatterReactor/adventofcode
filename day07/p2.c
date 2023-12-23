/*
    This program acts as a solution to day 7, part 2 of 2023's Advent of Code
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
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_HAND_HASH 0x6CCCCC
#define HANDS_SIZE MAX_HAND_HASH + 1

static uint_least16_t hands[HANDS_SIZE] = {0};

uint_least8_t card_to_num (const char c)
{
    
    if (isdigit(c))
        return c - '1';
    else switch (c) {
    case 'J': return 0;
    case 'T': return 9;
    case 'Q': return 10;
    case 'K': return 11;
    case 'A': return 12;
    default:
        fprintf(stderr, "unrecognized char %c", c);
        abort();
    }
}

uint_least8_t get_hand_type (const char *hand)
{
    uint_least8_t table[13] = {0}, max = 0, maxi = 0;
    for (size_t i = 0 ; i < 5; ++i)
        ++table[card_to_num(hand[i])];
    for (size_t i = 1 ; i < 13; ++i)
    {
        if (table[i] > max)
        {
            max = table[i];
            maxi = i;
        }
    }
    if (!max)
        return 6;
    table[maxi] += table[0];
    bool k3 = false, p1 = false;
    for (size_t i = 1 ; i < 13; ++i)
    {
        switch (table[i]) {
        case 5: return 6;
        case 4: return 5;
        case 3:
            if (p1) return 4;
            else k3 = true;
            break;
        case 2:
            if (k3) return 4;
            else if (p1) return 2;
            else p1 = true;
        case 1: break;
        }
    }
    if (k3) return 3;
    if (p1) return 1;
    return 0;
}

size_t hashcards (const char *hand)
{
    size_t h = 0;
    h = get_hand_type(hand);
    h <<= 20;
    for (size_t i = 0, en = 16; i < 5; ++i, en -= 4)
        h += (card_to_num(hand[i]) << en);
    return h;
}

void get_line_pair (char *line)
{
    uint_least16_t r = 0;
    char *it = line+6;
    while (isdigit(*(++it)));
    for (uint_fast32_t e = 1; isdigit(*(--it)); e *= 10)
    {
        r += (*it - '0') * e;
    }
    size_t c = hashcards(line);
    hands[c] = r;
}

uint_fast32_t process_hands (void)
{
    uint_fast32_t r = 0;
    for (size_t i = 0, count = 0; i < HANDS_SIZE; ++i)    
        if (hands[i] != 0)
        {
            r += ++count * hands[i];
            printf("hand: %6lX, bet: %3hu, count: %lu\n", i, hands[i], count);
        }
    return r;
}

int main (void)
{
    FILE* fp = fopen("input.txt", "r");

    char str[200] = {0};
    while (fgets(str, sizeof(str), fp) != NULL)
        get_line_pair(str);

    fclose(fp);

    printf("%lu\n", process_hands());

    return EXIT_SUCCESS;
}
