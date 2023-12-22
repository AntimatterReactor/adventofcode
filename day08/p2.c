/*
    This program acts as a solution to day 8, part 2 of 2023's Advent of Code
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
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INSTRUCTION_SIZE 300

typedef struct NodeType {
    uint_least16_t left_hash;
    uint_least16_t right_hash;
} node_t;

static char instruction[INSTRUCTION_SIZE] = {0};
static node_t nodes[26426] = {{0}};
static uint_least16_t beg[64] = {0}, *begit = beg;

#define HASH(C, x, y, z) ((C[x] << 10) + (C[y] << 5) + C[z] - 68705)
#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

size_t gcd (const size_t x, const size_t y)
{
    if (x + y == y || x + y == x)
        return MAX(x, y);
    return gcd(MAX(x, y) % MIN(x, y), MIN(x, y));
}

size_t lcm (const size_t x, const size_t y)
{
    if (x == 0 && y == 0)
        return 0;
    return (x / gcd(x, y)) * y;
}

void process_nodes_line (const char *line)
{
    node_t cur = {HASH(line, 7, 8, 9), HASH(line, 12, 13, 14)};
    int c = HASH(line, 0, 1, 2);
    nodes[c] = cur;
    if (line[2] == 'A')
        *(begit++) = c;
}

size_t run_instruct (size_t follow)
{
    size_t count = 0;
    for (int i = 0;; ++i)
    {
        if ((follow % 32) == ('Z' - 'A'))
            break;
        switch (instruction[i]) {
        case 'L':
            follow = nodes[follow].left_hash;
            break;
        case 'R':
            follow = nodes[follow].right_hash;
            break;
        default:
            i = -1;
            continue;
        }
        ++count;
    }
    return count;
}

int main (void)
{
    FILE* fp = fopen("input.txt", "r");

    fgets(instruction, INSTRUCTION_SIZE, fp);

    char str[200] = {0};
    fgets(str, sizeof(str), fp);
    while (fgets(str, sizeof(str), fp) != NULL)
        process_nodes_line(str);

    fclose(fp);

    size_t result = 1;
    begit = beg;
    do
    {
        result = lcm(result, run_instruct(*begit));
    } while (*(++begit) != 0);
    printf("%lu\n", result);

    return EXIT_SUCCESS;
}
