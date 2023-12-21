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

#define GRID_SIZE 140
#define GRID_PADDING 2

typedef struct PosType {
    uint_least16_t x;
    uint_least16_t y;
} pos_t;

char grid[GRID_SIZE + GRID_PADDING][GRID_SIZE + GRID_PADDING] = {{0}};
char resultgrid[GRID_SIZE][GRID_SIZE] = {{0}};

pos_t min_pos, max_pos;

pos_t process_line (const char *line, const size_t lno)
{
    memcpy(grid[lno + 1] + 1, line, GRID_SIZE);
    memset(resultgrid[lno], '.', GRID_SIZE);

    const char *pos = strchr(line, 'S');
    pos_t retpos = {0, 0};
    if (pos != NULL)
        retpos.x = pos - line + 1, retpos.y = lno + 1;
    return retpos;
}

pos_t traverse (char cur, const pos_t spos, const pos_t rpos)
{
    assert(abs(spos.x - rpos.x) < 2 && abs(spos.y - rpos.y) < 2);
    resultgrid[rpos.y - 1][rpos.x - 1] = cur;

#define MATCHTYPE(c, px, py) ((c << 8) + ((px + 2) << 2) + py + 2)

    const uint_least16_t tp = MATCHTYPE(cur, spos.x - rpos.x, spos.y - rpos.y);
    pos_t rdpos = rpos;
    switch (tp) {
    case MATCHTYPE('F', 1, 0):
    case MATCHTYPE('7', -1, 0):
    case MATCHTYPE('|', 0, -1): rdpos.y++; break;
                                
    case MATCHTYPE('F', 0, 1):
    case MATCHTYPE('L', 0, -1):
    case MATCHTYPE('-', -1, 0): rdpos.x++; break;

    case MATCHTYPE('L', 1, 0):
    case MATCHTYPE('J', -1, 0):
    case MATCHTYPE('|', 0, 1): rdpos.y--; break;
    
    case MATCHTYPE('J', 0, -1):
    case MATCHTYPE('7', 0, 1):
    case MATCHTYPE('-', 1, 0): rdpos.x--; break;

    default: assert(false);
    }

    min_pos.x = rdpos.x < min_pos.x ? rdpos.x: min_pos.x;
    min_pos.y = rdpos.y < min_pos.y ? rdpos.y: min_pos.y;
    max_pos.x = rdpos.x > max_pos.x ? rdpos.x: max_pos.x;
    max_pos.y = rdpos.y > max_pos.y ? rdpos.y: max_pos.y;
    return rdpos;
}


char deductS (const uint_least8_t coor)
{
    // coor -> NESW
    switch (coor) {
    case 0x6: return 'F'; //0110
    case 0xC: return 'L'; //1100
    case 0x9: return 'J'; //1001
    case 0x3: return '7'; //0011
    case 0xA: return '|'; //1010
    case 0x5: return '-'; //0101
    default: assert(false);
    }
}

pos_t traverseS (const pos_t cpos)
{
    uint_least8_t coor = 0;
    pos_t rpos = {0, 0};
    switch (grid[cpos.y - 1][cpos.x]) {
    case '|':
    case 'F':
    case '7':
        rpos.x = cpos.x, rpos.y = cpos.y - 1;
        coor += (1 << 3);
    default: break;
    }
    switch (grid[cpos.y + 1][cpos.x]) {
    case '|':
    case 'J':
    case 'L':
        rpos.x = cpos.x, rpos.y = cpos.y + 1;
        coor += (1 << 1);
    default: break;
    }
    switch (grid[cpos.y][cpos.x - 1]) {
    case '-':
    case 'F':
    case 'L':
        rpos.x = cpos.x - 1, rpos.y = cpos.y;
        coor += 1;
    default: break;
    }
    switch (grid[cpos.y][cpos.x + 1]) {
    case '-':
    case 'J':
    case '7':
        rpos.x = cpos.x + 1, rpos.y = cpos.y;
        coor += (1 << 2);
    default: break;
    }
    assert(rpos.x != 0 && rpos.y != 0);
    resultgrid[cpos.y - 1][cpos.x - 1] = deductS(coor);
    return rpos;
}

size_t process_grid (pos_t spos)
{
    assert(grid[spos.y][spos.x] == 'S');
    pos_t rpos = traverseS(spos);
    min_pos = max_pos = rpos;
    size_t count = 1;
    do {
        pos_t tt = traverse(grid[rpos.y][rpos.x], spos, rpos);
        spos = rpos;
        rpos = tt;
        ++count;
    } while (grid[rpos.y][rpos.x] != 'S');
    return count / 2;
}

size_t process_resultgrid (void)
{
    size_t parity = 0, count = 0;
    for (size_t i = 0; i < GRID_SIZE; ++i)
    {
        for (size_t j = 0; j < GRID_SIZE; ++j)
        {
            switch (resultgrid[i][j]) {
            case '.':
                count += parity % 2 ? 1 : 0;
                break;
            case 'F':
            case '7':
            case '|': parity++;
            default: break;
            }
        }
    }
    return count;
}

int main (void)
{
    char str[GRID_SIZE + GRID_PADDING] = {""};
    pos_t spos = {0, 0};
    FILE* fp = fopen("input.txt", "r");
    for (size_t i = 0; fgets(str, sizeof(str), fp) != NULL; ++i)
        if (!spos.x && !spos.y)
            spos = process_line(str, i);
        else process_line(str, i);
    fclose(fp);
    printf("%lu, %lu; max: %u, %u; min: %u, %u\n", process_grid(spos), process_resultgrid(), max_pos.x, max_pos.y, min_pos.x, min_pos.y);
    for (size_t i = 0; i < GRID_SIZE; ++i)
    {
        fwrite(resultgrid[i], sizeof(char), GRID_SIZE, stdout);
        putchar('\n');
    }
    return EXIT_SUCCESS;
}
