/*
    This program acts as a solution to the day 6 part 1 of AoC 2023
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

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

unsigned* processline (const char* restrict, unsigned* restrict, const size_t);
unsigned processdata (const unsigned*, const unsigned*, const size_t);

int main(void)
{
    char str[64] = {""};
    unsigned tarr[4] = {0}, darr[4] = {0};
    const size_t rlen = 4;
    uint_fast32_t product = 0;
    FILE* fp = fopen("../inputs/input6.txt", "r");

    fgets(str, sizeof(str), fp);
    processline(strchr(str, ':') + 1, tarr, rlen);

    fgets(str, sizeof(str), fp);
    processline(strchr(str, ':') + 1, darr, rlen); 

    fclose(fp);

    product = processdata(tarr, darr, rlen);

    printf("%lu\n", product);
    return EXIT_SUCCESS;
}

unsigned reverse_number10 (unsigned x) {
    unsigned r = 0;
    while (x > 0)
    {
        r = (r * 10) + (x % 10);
        x /= 10;
    }
    return r;
}

unsigned padding_number10 (unsigned x, const unsigned en) {
    while (en > x)
        x *= 10;
    return x;
}

unsigned* processline
(const char* restrict str, unsigned* restrict arr, const size_t rlen)
{
    unsigned en = 1, val = 0, ti = 0, pd = 0;
    for(; *str != '\n' && *str != '\0'; ++str)
    {
        if (isdigit(*str))
        {
            val += (*str - '0') * (en *= 10) / 10;
            pd = 1;
        }
        else if (pd)
        {
            arr[ti++] = padding_number10(reverse_number10(val), en / 10);
            assert(ti <= rlen);
            pd = 0;
            val = 0;
            en = 1;
        }
    }
    if (pd && val)
    {
        arr[ti++] = padding_number10(reverse_number10(val), en / 10);
        assert(ti <= rlen);
        pd = 0;
        val = 0;
        en = 1;
    }
    return arr;
}

unsigned processdata (const unsigned* tarr, const unsigned* darr, const size_t rlen)
{
    unsigned p = 1;
    for (size_t i = 0; i < rlen; ++i)
    {
        unsigned np = 0, r = 0;
        for (unsigned j = 1; j < tarr[i]; ++j)
        {
            if ((tarr[i] - j) * j > darr[i])
            {
                if (!np)
                    np = 1;
                ++r;
            }
            else if (np)
                break;
        }
        p *= r;
    }
    return p;
}
