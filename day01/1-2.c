/*
    This program acts as a solution to the day 1 part 2 of AoC 2023
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
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Assumes str all lowercase alphabet
uint_fast32_t numericmagify(const char* str, const size_t len)
{
    size_t tlen = len * 5 < sizeof(uint_fast32_t) * 8 ? len : sizeof(uint_fast32_t) * 3 / 2;
    uint_fast32_t r = 0;
    for (size_t i = 0; i < tlen; i++) {
        r += (str[i] - '`') << (5 * i);
    }
    return r;
}

#define MCOMPARE(BUF, SSTR, LEN) numericmagify(BUF, LEN) == numericmagify(SSTR, LEN)

int process_line(const char* buf, const size_t len)
{
    int x = 0, y = 0, xc = 0, yc = 0;
    for (size_t i = 0; i < len; i++)
    {
        switch (buf[i]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            x = !xc ? 10 * (buf[i] - '0') : x, xc = 1;
            break;
        case 'o':
            if (!xc && MCOMPARE(buf+i, "one", 3))
                x = 10, xc = 1;
            break;
        case 't':
            if (!xc && MCOMPARE(buf+i, "two", 3))
                x = 20, xc = 1;
            else if (!xc && MCOMPARE(buf+i, "three", 5))
                x = 30, xc = 1;
            break;
        case 'f':
            if (!xc && MCOMPARE(buf+i, "four", 4))
                x = 40, xc = 1;
            else if (!xc && MCOMPARE(buf+i, "five", 4))
                x = 50, xc = 1;
            break;
        case 's':
            if (!xc && MCOMPARE(buf+i, "six", 3))
                x = 60, xc = 1;
            if (!xc && MCOMPARE(buf+i, "seven", 5))
                x = 70, xc = 1;
            break;
        case 'e':
            if (!xc && MCOMPARE(buf+i, "eight", 5))
                x = 80, xc = 1;
            break;
        case 'n':
            if (!xc && MCOMPARE(buf+i, "nine", 4))
                x = 90, xc = 1;
            break;
        default:
            break;
        }
        switch (buf[len-i-1]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            y = !yc ? (buf[len-i-1] - '0') : y;
            yc = 1;
            break;
        case 'o':
            if (!yc && MCOMPARE(buf+len-i-1, "one", 3))
                y = 1, yc = 1;
            break;
        case 't':
            if (!yc && MCOMPARE(buf+len-i-1, "two", 3))
                y = 2, yc = 1;
            else if (!yc && MCOMPARE(buf+len-i-1, "three", 5))
                y = 3, yc = 1;
            break;
        case 'f':
            if (!yc && MCOMPARE(buf+len-i-1, "four", 4))
                y = 4, yc = 1;
            else if (!yc && MCOMPARE(buf+len-i-1, "five", 4))
                y = 5, yc = 1;
            break;
        case 's':
            if (!yc && MCOMPARE(buf+len-i-1, "six", 3))
                y = 6, yc = 1;
            if (!yc && MCOMPARE(buf+len-i-1, "seven", 5))
                y = 7, yc = 1;
            break;
        case 'e':
            if (!yc && MCOMPARE(buf+len-i-1, "eight", 5))
                y = 8, yc = 1;
            break;
        case 'n':
            if (!yc && MCOMPARE(buf+len-i-1, "nine", 4))
                y = 9, yc = 1;
            break;
        default:
            break;
        }
    }
    printf("%d\n", x+y);
    return x + y;
}

int main()
{
    char str[64] = {""};
    int total = 0;
    FILE* fp = fopen("../inputs/input1.txt", "r");
    while (fgets(str, sizeof(str), fp) != NULL) {
        total += process_line(str, strlen(str));
    }
    fclose(fp);
    printf("%d\n", total);
    return 0;
}
