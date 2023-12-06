#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

const bool process_line(const char *str, const size_t len, const int de)
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

int main()
{
    char str[256] = {""};
    uint_fast32_t total = 0;
    FILE* fp = fopen("../inputs/input2.txt", "r");
    for (int i = 1; fgets(str, sizeof(str), fp) != NULL; ++i) {
        total += process_line(str, strnlen(str, sizeof(str)), i) ? i : 0;
        memset(str, 0, sizeof(str));
        //printf("%s\n", str);
    }
    fclose(fp);
    printf("%lu\n", total);
    return EXIT_SUCCESS;
}