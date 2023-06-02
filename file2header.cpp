#include "File2Hex2Header.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("%d\n", argc);
        printf("example:\n  $ %s file header.h \n", argv[0]);
        return -1;
    }

    File2Header(argv[1], argv[2]);
    return 0;
}