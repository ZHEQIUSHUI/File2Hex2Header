#include "File2Hex2Header.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("%d\n", argc);
        printf("example:\n  $ %s header.h file\n", argv[0]);
        return -1;
    }
    
    return 0;
}