#ifndef BUF_IO_H
#define BUF_IO_H

#define BUF_SIZE 4096

// define a new bfile (for buffered file) type
typedef struct _bfile
{
    int fd;
    char buffer[BUF_SIZE];
    int pos; 
    int size;
    // TODO: fill me in
    // you'll need to add whatever fields are necessary
    // here to buffer and track the buffer for one file
} bfile;

// buffered open; open filename for reading
bfile *bopen(char *filename);

// buffered read; read num_bytes into userbuf from file
int bread(bfile *file, char *userbuf, size_t num_bytes);

// buffered close; close file
int bclose(bfile *file);




#endif
