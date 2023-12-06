#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

const uint_fast32_t process_line(const char* buf, const size_t len)
{
    uint_fast32_t z = 0;
    size_t k = 0;
    for(size_t i = 0; i < len; i++)
        if (isdigit(buf[i]))
            z += (buf[i] - '0') << (4 * k++);

    // printf("%lu %lu ", z, k);
    return 10 * (z % (1 << 4)) + (z / (1 << (4 * (k - 1))));
}

int main()
{
    char str[64] = {""};
    uint_fast32_t total = 0;
    FILE* fp = fopen("../inputs/input1.txt", "r");
    while (fgets(str, sizeof(str), fp) != NULL) {
        total += process_line(str, strnlen(str, sizeof(str)));
        // printf("%lu\n", total);
    }
    fclose(fp);
    printf("%lu\n", total);
    return EXIT_SUCCESS;
}