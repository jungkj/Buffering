#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // 2 arguments are required
    // - the name of the file to print
    // - the number of bytes to get in each read call
    if (argc != 3)
    {
        printf("usage: %s filename bytes_per_read\n", basename(argv[0]));
        exit(1);
    }

    // must read at least one byte at a time
    int bytes_per_read = atoi(argv[2]);
    if (bytes_per_read < 1)
    {
        printf("error: must read at least one byte per iteration\n");
        printf("usage: %s filename bytes_per_read\n", basename(argv[0]));
        exit(1);
    }

    // open the file for reading
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("%s: no such file or directory\n", argv[1]);
        exit(1);
    }

    // allocate an array with enough space to hold all of the
    // bytes from one read, plus 1 for the null terminator
    char *buf = (char *)malloc((bytes_per_read+1)*sizeof(char));
    if (buf == NULL)
    {
        // always check for errors!
        printf("error: out of memory\n");
        exit(1);
    }

    // read the file N bytes at a time
    // note: read might return less than N bytes, which is not an error
    int read_return;
    while ((read_return = read(fd, buf, bytes_per_read)) >= 1)
    {
        // add the null terminator so that we can print the
        // array as a C-string
        buf[read_return] = '\0';
        printf("%s", buf);
    }

    // always clean up your own memory!
    free(buf);

    // if read returned -1, then that is an error
    if (read_return == -1)
    {
        printf("%s: read error\n", argv[1]);
        exit(1);
    }

    // always close your files!
    if(close(fd) != 0)
    {
        printf("%s: close error\n", argv[1]);
    }

    return 0;
}
