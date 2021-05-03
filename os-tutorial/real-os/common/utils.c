#include "kernel_types.h"
#include "utils.h"

uint8_t* memory_move (uint8_t* to, uint8_t *from, uint32_t n)
{
    if (to == from) return to;
    if (to > from && to < (from+n)) {
        for (int i = n - 1; i >= 0; i--)
            *(to+i) = *(from+i);
    } else {
        for (uint32_t i = 0; i < n; ++i)
            *(to+i) = *(from+i);
    }
    return to;
}

void int_to_str (int32_t n, char str[])
{
    int32_t i = 0;
    int32_t sign = n;
    if (n < 0) n = -n;
    /* assume str has sufficient space to hold this integer */
    do {
        str[i++] = n % 10 + '0';
        n /= 10;
    } while (n);
    if (sign < 0) str[i++] = '-';
    /* quick reverse */
    for (int l = 0, r = i - 1; l < r; l++, r--) {
        char tmp = str[l];
        str[l] = str[r];
        str[r] = tmp;
    }
    str[i] = '\0';
    return;
}

