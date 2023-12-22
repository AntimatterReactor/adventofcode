/*
    This program acts as a solution to day 2, part 2 of 2023's Advent of Code
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
#include <ctype.h>

uint_fast32_t process_line(const char *str, const size_t len, const int deb)
{
    uint_fast32_t r=0, g=0, b=0, s=0;
    char k = 0;
    const char *mstr = strchr(str, ':') + 1;
    for (size_t i = 0; i < len; ++i) {
        if (isdigit(mstr[i])) {
            k = mstr[i+1] == ' ' ? mstr[i+2] : mstr[i+3];
            switch(k){
            case 'r':
                r = r < (s = atoi(mstr+i)) ? s : r;
                break;
            case 'g':
                g = g < (s = atoi(mstr+i)) ? s : g;
                break;
            case 'b':
                b = b < (s = atoi(mstr+i)) ? s : b;
                break;
            default:
                break; 
            }
        }
    }
    printf("%d: %lu, %lu, %lu\n", deb, r,g,b);
    return r*g*b;
}

int main(void)
{
    char str[256] = {""};
    uint_fast32_t total = 0;
    FILE* fp = fopen("inputs/input2.txt", "r");
    for (int i = 1; fgets(str, sizeof(str), fp) != NULL; ++i) {
        total += process_line(str, strlen(str), i);
        memset(str, 0, sizeof(str));
        //printf("%s\n", str);
    }
    fclose(fp);
    printf("%lu\n", total);
    return EXIT_SUCCESS;
}
