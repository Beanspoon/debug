#include "nosys.h"

int _close(int file)
{
    (void)file;
    return -1;
}

int _lseek(int file, int ptr, int dir)
{
    (void)file; (void)ptr; (void)dir;
    return -1;
}

int _read(int file, char *ptr, int length)
{
    (void)file; (void)ptr; (void)length;
    return -1;
}

int _write(int file, char *ptr, int length)
{
    (void)file; (void)ptr; (void)length;
    return -1;
}