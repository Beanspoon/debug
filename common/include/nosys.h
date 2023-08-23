#ifndef NOSYS_H
#define NOSYS_H

int _close(int file);

int _lseek(int file, int ptr, int dir);

int _read(int file, char *ptr, int length);

int _write(int file, char *ptr, int length);

#endif // NOSYS_H