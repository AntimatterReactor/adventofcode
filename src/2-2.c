#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

const uint_fast32_t process_line(const char *str, const size_t len, const int deb)
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

int main()
{
    char str[256] = {""};
    uint_fast32_t total = 0;
    FILE* fp = fopen("../inputs/input2.txt", "r");
    for (int i = 1; fgets(str, sizeof(str), fp) != NULL; ++i) {
        total += process_line(str, strnlen(str, sizeof(str)), i);
        memset(str, 0, sizeof(str));
        //printf("%s\n", str);
    }
    fclose(fp);
    printf("%lu\n", total);
    return EXIT_SUCCESS;
}