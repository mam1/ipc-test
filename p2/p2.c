

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

#include "p2.h"


/* ipc data - memory mapped */
typedef	struct {
	uint32_t    sch[_DAYS_PER_WEEK][_NUMBER_OF_CHANNELS][_SCHEDULE_SIZE];	// system schedule
	int			force_update;		// force daemon to update channel
    struct {
    	int 		c_state;		// 0 = off, 1 = on	
		int 		c_mode; 		// Control mode: 0-manual, 1-time, 2-time & sensor, 3-cycle
		int			on_sec ;		// on cycle in seconds
		int 		off_sec;		// off cycle in seconds    
	} c_dat[_NUMBER_OF_CHANNELS];
	struct{
		int			temp;
		int			humidity;
		int			lup_sec;
		int			lup_min;
		int			lup_hour;
		int			lup_wday;
	} s_dat[_NUMBER_OF_SENSORS];

} IPC_DAT;

int ipc_open(char *fname){
	int 		fd;
	mode_t 		mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    fd = open(fname, O_RDWR);
    if(fd == -1){
        printf("\n*** error opening system data file\r\n");
        perror(fname);
        printf("*** terminating program\n\n");
        exit(1);
    }
	printf("file descriptor %i returned from open\n",fd);
	return fd;
}

void *ipc_map(int fd, int size){
	void		*data;
	data = mmap((caddr_t)0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if((caddr_t)data == (caddr_t)(-1)){
        printf("\n*** error mapping ipc data file\r\n");
        perror("mmap");
        printf("*** terminating program\n\n");
        exit(1);
	}
	printf("file mapped to memory\n");
	return data;
}

void ipc_close(int fd, void *data, int size){
	if(munmap(data, size) == -1){
        perror ("munmap");
        exit(1);
    }
	close(fd);
	return;
}

int main(void){

	IPC_DAT			com_block;
	char			*fname = "/home/rsync-OSX/ipc.dat";
	int 			fd;
	int 			data_size;
	void			*data;
	int 			*ptr; 
	int 			value, hvalue;

	long page_size = sysconf (_SC_PAGESIZE);
	data_size = 2 * (int)page_size;
	printf("\n ***** ipc test  p2 ****\n\n");
	printf("page size %i\n",(int)page_size);
	printf("system control block size %i\n",sizeof(com_block));
	printf("     system schedule size %i\n",sizeof(com_block.sch));
	printf("        channel data size  %i\n",sizeof(com_block.c_dat));
	printf("         sensor data size  %i\n",sizeof(com_block.s_dat));
	printf("                file size %i\n",data_size);
	printf("\nwasted memory %i\n\n", 2*(int)page_size - sizeof(com_block));

	fd = ipc_open(fname);				// create/open ipc file
	data = ipc_map(fd,data_size);		// map file to memory
	memcpy(&com_block,data,sizeof(com_block));	// move shared memory data to local structure		
	value = com_block.force_update;
	printf(" initial value %i\n",value);
	hvalue = -1;
	while(value){
		if(hvalue != value){
			printf(" <%i>\n",value);
			hvalue = value;
		}
		memcpy(&com_block,data,sizeof(com_block));	// move shared memory data to local structure
		value = com_block.force_update;
	}

	printf("\nnormal termination\n\n");
	return 0;
}
