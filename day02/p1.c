/*
    This program acts as a solution to day 2, part 1 of 2023's Advent of Code
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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool process_line(const char *str, const size_t len)
{
    const char *mstr = strchr(str, ':') + 1;
    for (size_t i = 0; i < len; ++i) {
        if (isdigit(mstr[i])) {
            if (mstr[i+1] == ' ' || mstr[i+1] <= '2'
            || (mstr[i+1] <= '4' && mstr[i+3] == 'b')
            || (mstr[i+1] <= '3' && mstr[i+3] == 'g')){
                i += 2;
                continue;
            }
            else return false;
        }
    }
    return true;
}

int main(void)
{
    char str[256] = {""};
    uint_fast32_t total = 0;
    FILE* fp = fopen("input.txt", "r");
    for (uint_fast32_t i = 1; fgets(str, sizeof(str), fp) != NULL; ++i) {
        total += process_line(str, strlen(str)) ? i : 0;
        memset(str, 0, sizeof(str));
        //printf("%s\n", str);
    }
    fclose(fp);
    printf("%lu\n", total);
    return EXIT_SUCCESS;
}
