#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// TODO: add whatever other header files you need

#include "buf_io.h"

// buffered open; open filename for reading
bfile *bopen(char *filename)
{
	// First open file
	int fd = open(filename, O_RDONLY);
	if (fd == -1){
		return NULL;
	}
	// Initialize bf buffer struct
	// make bf's fd = file fd
	// set bf index to end of buffer
	// set bf ->size = 0 since buffer is empty for now
	bfile *bf = malloc(sizeof(bfile));
	bf->fd = fd; 
	bf->pos = BUF_SIZE;
	bf->size = 0;

	return bf; 
}

// buffered read; read num_bytes into userbuf from file
int bread(bfile *file, char *userbuf, size_t num_bytes)
{
	int total_bytes_read = 0;
	int bytes_left_in_buffer = BUF_SIZE - file->pos; 
	// if no bytes left, copy them to user buffer
	if (bytes_left_in_buffer > 0){
		int bytes_to_copy = num_bytes > bytes_left_in_buffer ? bytes_left_in_buffer : num_bytes; 
		memcpy(userbuf, file->buffer + file->pos, bytes_to_copy);
		file->pos += bytes_to_copy;
		total_bytes_read += bytes_to_copy;
		userbuf = (char*)userbuf + bytes_to_copy;
		num_bytes -= bytes_to_copy;
	
	}

	//if need to read more bytes, read into user buff
	if (num_bytes > 0){
		int bytes_read = read(file->fd, userbuf, num_bytes);
		total_bytes_read += bytes_read;
	}

	return total_bytes_read;
    return 0;
}

// buffered close; close file
int bclose(bfile *file)
{
	//write remaining buffer bytes to disk
	int bytes_written = write(file->fd, file->buffer, file->pos);
	if (bytes_written == -1){
		return -1;
	}
    	
	int close_return = close(file->fd);
	if (close_return == -1){
		return -1;
	}

	file->fd = -1;
    
    return 0;
}
