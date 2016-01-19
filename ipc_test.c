#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>    //sleep
#include <stdint.h>   //uint_8, uint_16, uint_32, etc.

#include "ipc.h"


int main(void){
	char			*fname = "/home/rsync-OSX/ipc.dat";
	int 			fd;
	int 			filesize;
	void			*data;
	int				pages;
	IPC_DAT			com_block;

	printf("\n**** test_ipc ****\n\n");

	/* figure out size of the file in multiples of page size */
	long page_size = sysconf (_SC_PAGESIZE);
	pages = sizeof(com_block) / page_size;
	if(pages < 1) pages = 1;
	else if(sizeof(com_block) % page_size != 0) pages += 1;
	printf("pages = %i\n", pages);
	filesize = pages * (int)page_size;

	fd = ipc_open(fname);						// create/open ipc file
	data = ipc_map(fd,filesize);				// map file to memory
	memcpy(&com_block,data,sizeof(com_block));	// move shared memory data to local structure



	printf("normal termination\n\n");
	return 0;
}