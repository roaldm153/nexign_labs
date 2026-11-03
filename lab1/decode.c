/*
 * Восстановление пароля из зашифрованного эталона legacy.c.
 *
 * Эталон — длины списков из массива a[] оригинала (сколько z() в элементе).
 * Оригинал шифрует ввод операциями по кругу из семи, позиция k % 7:
 *   0: ^ 0x63   1: ^ 48   2: << 4   3: << 2   4: * 55   5: + 97   6: + 44
 * Здесь к каждому значению применяется обратная операция.
 */
#include <stdio.h>

static const int encrypted[] = {
    5,    92,  1552, 412, 6765, 202, 139, 0,   95,  1760, 460,  5775, 197,
    145,  17,  85,   1600, 380, 5665, 202, 162, 10,  94,  1648, 380,  6105,
    207,  152, 26,   111, 1856, 416, 5555, 192, 142, 10,  94,  1552, 456,
    6655, 192, 94,   87,  4,    784, 200,  3025, 145, 99,  30,
};

static int decrypt(int k, int e)
{
    switch (k % 7) {
    case 0: return e ^ 0x63;
    case 1: return e ^ 48;
    case 2: return e >> 4;
    case 3: return e >> 2;
    case 4: return e / 55;
    case 5: return e - 97;
    default: return e - 44;
    }
}

int main(void)
{
    int n = (int)(sizeof encrypted / sizeof encrypted[0]);

    for (int k = 0; k < n; k++)
        putchar(decrypt(k, encrypted[k]));
    putchar('\n');
    return 0;
}
