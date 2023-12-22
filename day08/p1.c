/*
    This program acts as a solution to the day 8 part 1 of AoC 2023
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

#define HASH(C, x, y, z) ((C[x] << 10) + (C[y] << 5) + C[z] - 68705)

void process_nodes_line (const char *line)
{
    node_t cur = {HASH(line, 7, 8, 9), HASH(line, 12, 13, 14)};
    nodes[HASH(line, 0, 1, 2)] = cur;
}

size_t run_instruct (void)
{
    size_t follow = 0, count = 0;
    for (int i = 0;; ++i)
    {
        if (follow == HASH("Z", 0, 0, 0))
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

    printf("%lu\n", run_instruct());

    return EXIT_SUCCESS;
}
